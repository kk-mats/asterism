#include "scatter_plot_model.hpp"

namespace asterism
{

scatter_plot_model::scatter_plot_model(QObject *parent) noexcept
	: QAbstractTableModel(parent)
{}

int scatter_plot_model::rowCount(const QModelIndex &parent [[maybe_unused]]) const noexcept
{
	return this->current_layer_!=nullptr ? this->current_layer_->width() : 0;
}

int scatter_plot_model::columnCount(const QModelIndex &parent [[maybe_unused]]) const noexcept
{
	return this->current_layer_!=nullptr ? this->current_layer_->width() : 0;
}

QVariant scatter_plot_model::data(const QModelIndex &index, int role) const noexcept
{
	if(index.isValid() && role==Qt::DisplayRole)
	{
		auto r=*this->current_layer_;
		auto c=r[grid_2d_coordinate::to_linear(index.row(), index.column())];
		return c;
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


void scatter_plot_model::add_heatmap_layers(QList<heatmap_layer> &&layers) noexcept
{
	this->layers_->append(layers);
	this->change_current_layer(this->createIndex(this->layers_->size()-1, 0));
}

void scatter_plot_model::add_heatmap_layer(heatmap_layer &&heatmap_layer) noexcept
{
	this->layers_->push_back(std::move(heatmap_layer));
	this->change_current_layer(this->createIndex(this->layers_->size()-1, 0));
}

bool scatter_plot_model::update() noexcept
{
	for(auto &&h:*this->layers_)
	{
		if(!h.update())
		{
			return false;
		}
	}

	return true;
}

const std::shared_ptr<QList<heatmap_layer>> &scatter_plot_model::layers() const noexcept
{
	return this->layers_;
}

bool scatter_plot_model::insertRows(int row, int count, const QModelIndex &parent) noexcept
{
	const int end=row+count;
	this->beginInsertRows(parent, row, end-1);

	for(; row<end; ++row)
	{
		this->layers_->append(heatmap_layer());
	}

	this->endInsertRows();
}

bool scatter_plot_model::setData(const QModelIndex &index, const QVariant &value, int role) noexcept
{
	if(!index.isValid() || role!=Qt::EditRole)
	{
		return false;
	}


}

void scatter_plot_model::change_current_layer(const QModelIndex &index) noexcept
{
	this->beginResetModel();
	this->current_index_=index.row();
	this->current_layer_=&(*this->layers_)[this->current_index_];
	this->endResetModel();
}

}
