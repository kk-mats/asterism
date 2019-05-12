#include "scatter_plot_widget.hpp"

namespace asterism
{

scatter_plot_model::scatter_plot_model(QObject *parent) noexcept
	: QAbstractTableModel(parent)
{}

int scatter_plot_model::rowCount(const QModelIndex &) const noexcept
{
	return this->current_layer_!=nullptr ? this->current_layer_->width() : 0;
}

int scatter_plot_model::columnCount(const QModelIndex &) const noexcept
{
	return this->current_layer_!=nullptr ? this->current_layer_->width() : 0;
}

QVariant scatter_plot_model::data(const QModelIndex &index, int role) const noexcept
{
	if(index.isValid() && role==Qt::BackgroundColorRole)
	{
		auto r=*this->current_layer_;
		auto c=r[grid_2d_coordinate::to_linear(index.row(), index.column())];
		return c;
	}

	return QVariant();
}

QVariant scatter_plot_model::headerData(int, Qt::Orientation, int role) const noexcept
{
	if(role==Qt::SizeHintRole)
	{
		return QSize(1, 1);
	}
	return QVariant();
}

void scatter_plot_model::change_method(const int method_index) noexcept
{
	this->beginResetModel();
	if(method_index==0)
	{
		this->current_layer_->change_method(heatmap_layer::method::clone_pair_size());
	}
	else
	{
		this->current_layer_->change_method(heatmap_layer::method::mismatch_rate());
	}
	this->endResetModel();
}

scatter_plot_widget::scatter_plot_widget(const detection_results *results, QWidget *parent)
	: QTableView(parent), results_(results)
{
	auto p=this->palette();
	p.setColor(QPalette::Inactive, QPalette::Highlight, Qt::gray);
	this->setPalette(p);
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

void scatter_plot_widget::select_grid(const QModelIndex &index) noexcept
{
	if(index.isValid() && this->model_->previous_!=index)
	{
		this->setCurrentIndex(index);
		this->model_->previous_=index;
		auto x=this->results_->file_at(index.row()), y=this->results_->file_at(index.column());
		emit current_grid_changed(x->canonical_file_path(), y->canonical_file_path(), 100);
		if(this->model_->current_layer_->method_index()!=0)
		{
			emit current_grid_changed(x, y, this->model_->current_layer_->primitive());
		}
	}
}
}
