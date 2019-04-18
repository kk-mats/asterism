#include "scatter_plot_model.hpp"

namespace asterism
{

scatter_plot_model::scatter_plot_model(QObject *parent) noexcept
	: QAbstractTableModel(parent)
{}

int scatter_plot_model::rowCount(const QModelIndex &parent [[maybe_unused]]) const noexcept
{
	return this->heatmap_layer_.width();
}

int scatter_plot_model::columnCount(const QModelIndex &parent [[maybe_unused]]) const noexcept
{
	return this->heatmap_layer_.width();
}

QVariant scatter_plot_model::data(const QModelIndex &index, int role) const noexcept
{
	if(index.isValid() && role==Qt::DisplayRole)
	{
		return this->heatmap_layer_[grid_2d_coordinate::to_linear(index.row(), index.column())];
	}

	return QVariant();
}

QVariant scatter_plot_model::headerData(int section [[maybe_unused]], Qt::Orientation orientation [[maybe_unused]], int role) const noexcept
{
	if(role==Qt::SizeHintRole)
	{
		return QSize(1, 1);
	}
	return QVariant();
}


void scatter_plot_model::set_heatmap_layer(heatmap_layer &&heatmap_layer) noexcept
{
	this->beginResetModel();
	this->heatmap_layer_=heatmap_layer;
	this->endResetModel();
}

bool scatter_plot_model::update(const file_index &file_index) noexcept
{
	return this->heatmap_layer_.update(file_index);
}

}
