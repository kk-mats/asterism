#include "layer_list_model.hpp"

namespace asterism
{
layer_list_model::layer_list_model(const std::shared_ptr<const QList<heatmap_layer>> &layers, QObject *parent) noexcept
	: QAbstractListModel(parent), layers_(layers)
{}

int layer_list_model::rowCount(const QModelIndex &parent) const
{
	return this->layers_->size();
}

QVariant layer_list_model::data(const QModelIndex &index, int role) const
{
	if(index.isValid() && role==Qt::DisplayRole && this->layers_->size()>0)
	{
		auto i=this->layers_->begin();
		std::advance(i, index.row());
		return i->name();
	}
	return QVariant();
}

}

