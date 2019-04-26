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
	if(index.isValid()&&role==Qt::DisplayRole)
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

void scatter_plot_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if(index.data().canConvert<QColor>())
	{
		painter->fillRect(option.rect, index.data().value<QColor>());
	}
}

QSize scatter_plot_delegate::sizeHint(const QStyleOptionViewItem &option [[maybe_unused]], const QModelIndex &index [[maybe_unused]]) const
{
	return QSize(grid_size, grid_size);
}

scatter_plot_widget::scatter_plot_widget(QWidget *parent)
	: QTableView(parent)
{
	this->setModel(this->model_);
	this->setItemDelegate(new scatter_plot_delegate(parent));

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

void scatter_plot_widget::select_grid(const QModelIndex &index) noexcept
{
	if(index.isValid() && this->model_->previous_!=index)
	{
		this->model_->previous_=index;
		emit current_grid_changed(QString::number(index.row()), QString::number(index.column()), 100);
	}
}
}
