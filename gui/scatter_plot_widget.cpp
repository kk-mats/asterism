#include "scatter_plot_widget.hpp"

namespace asterism
{

scatter_plot_model::scatter_plot_model(QObject *parent) noexcept
	: QAbstractTableModel(parent)
{}

int scatter_plot_model::rowCount(const QModelIndex &parent [[maybe_unused]] ) const noexcept
{
	return this->current_layer_!=nullptr ? this->current_layer_->width() : 0;
}

int scatter_plot_model::columnCount(const QModelIndex &parent [[maybe_unused]] ) const noexcept
{
	return this->current_layer_!=nullptr ? this->current_layer_->width() : 0;
}

QVariant scatter_plot_model::data(const QModelIndex &index, int role) const noexcept
{
	if(index.isValid()&&role==Qt::BackgroundColorRole)
	{
		auto r=*this->current_layer_;
		auto c=r[grid_2d_coordinate::to_linear(index.row(), index.column())];
		return c;
	}

	return QVariant();
}

QVariant scatter_plot_model::headerData(int section [[maybe_unused]] , Qt::Orientation orientation [[maybe_unused]] , int role) const noexcept
{
	if(role==Qt::SizeHintRole)
	{
		return QSize(1, 1);
	}
	return QVariant();
}


scatter_plot_widget::scatter_plot_widget(const detection_results *results, QWidget *parent)
	: QTableView(parent), results_(results)
{
	this->setSelectionMode(QAbstractItemView::SingleSelection);

	this->setModel(this->model_);

	this->verticalHeader()->hide();
	this->horizontalHeader()->hide();
	this->verticalHeader()->setMinimumSectionSize(grid_size);
	this->horizontalHeader()->setMinimumSectionSize(grid_size);
	this->verticalHeader()->setDefaultSectionSize(grid_size);
	this->horizontalHeader()->setDefaultSectionSize(grid_size);

	connect(this, &scatter_plot_widget::clicked, this, &scatter_plot_widget::select_grid);
}


void scatter_plot_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->model_->beginResetModel();
	this->model_->current_layer_=layer;
	this->model_->endResetModel();
}

void scatter_plot_widget::update_layer() noexcept
{
	this->model_->beginResetModel();
	this->model_->endResetModel();
}

void scatter_plot_widget::change_rule(const int index) noexcept
{
	if(index==0)
	{
		this->model_->current_layer_->change_rule(heatmap_layer::rule::clone_pair_size());
	}
	else
	{
		this->model_->current_layer_->change_rule(heatmap_layer::rule::matching_rate());
	}
}

void scatter_plot_widget::select_grid(const QModelIndex &index) noexcept
{
	if(index.isValid() && this->model_->previous_!=index)
	{
		this->setCurrentIndex(index);
		this->model_->previous_=index;
		emit current_grid_changed(this->results_->file_at(index.row())->canonical_file_path(), this->results_->file_at(index.column())->canonical_file_path(), 100);
	}
}
}
