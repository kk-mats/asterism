#include "layer_list_model.hpp"

namespace asterism
{

void layer_list_model::set_detection_results(const shared_list<detection_result> &results) noexcept
{
	this->beginResetModel();
	for(const auto &r:results)
	{
		this->layers_.emplace_back(r);
	}
	this->endResetModel();
}

int layer_list_model::rowCount(const QModelIndex &parent) const
{
	return this->layers_.size();
}

QVariant layer_list_model::data(const QModelIndex &index, int role) const
{
	if(index.isValid() && role==Qt::DisplayRole)
	{
		auto i=this->layers_.begin();
		std::advance(i, index.row());

		return std::visit(heatmap_layer_name_visitor(), *i);
	}
	return QVariant();
}

}

