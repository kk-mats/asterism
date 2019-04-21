#include "results_list_model.hpp"

namespace asterism
{

void results_list_model::set_results(const shared_set<detection_result> &results) noexcept
{
	this->beginResetModel();
	this->results_list_=results.toList().toVector();
	this->endResetModel();
}

int results_list_model::rowCount(const QModelIndex &parent) const
{
	return this->results_list_.size();
}

QVariant results_list_model::data(const QModelIndex &index, int role) const
{
	if(index.isValid() && role==Qt::DisplayRole)
	{
		return this->results_list_[index.row()]->environment().name();
	}
	return QVariant();
}

}

