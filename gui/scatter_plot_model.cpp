#include "scatter_plot_model.hpp"

namespace asterism
{

scatter_plot_model::scatter_plot_model(QObject *parent) noexcept
	: QAbstractTableModel(parent)
{}

int scatter_plot_model::rowCount(const QModelIndex &parent[[maybe_unused]]) const noexcept
{
	return this->heatmap_layer_.width();
}

int scatter_plot_model::columnCount(const QModelIndex &parent[[maybe_unused]]) const noexcept
{
	return this->heatmap_layer_.width();
}

QVariant scatter_plot_model::data(const QModelIndex &index, int role) const noexcept
{
	if(index.isValid() && role==Qt::DisplayRole)
	{
		return this->heatmap_layer_[grid_2d_coordinate(index.row(), index.column())];
	}

	return QVariant();
}

QVariant scatter_plot_model::headerData(int section, Qt::Orientation orientation, int role) const noexcept
{
	if(role==Qt::SizeHintRole)
	{
		return QSize(1, 1);
	}
	return QVariant();
}


void scatter_plot_model::set_heatmap_layer(const heatmap_layer &heatmap_layer) noexcept
{
	this->heatmap_layer_=heatmap_layer;
}

}
