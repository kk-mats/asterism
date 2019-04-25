#include "layer_list_model.hpp"

namespace asterism
{
layer_list_model::layer_list_model(QObject *parent) noexcept
	: QAbstractListModel(parent)
{}

int layer_list_model::rowCount(const QModelIndex &parent) const
{
	return this->layers_.size();
}

QVariant layer_list_model::data(const QModelIndex &index, int role) const
{
	if(index.isValid() && role==Qt::DisplayRole && this->layers_.size()>0)
	{
		return this->layers_[index.row()]->name();
	}
	return QVariant();
}

void layer_list_model::emplace_clone_size_heatmap_layers(const shared_list<detection_result> &results) noexcept
{
	const auto head=this->layers_.size();
	this->insertRows(head, results.size());
	for(auto i=0; i<results.size(); ++i)
	{
		this->setData(this->index(head+i, 0), QVariant::fromValue(results[i]));
	}
}

void layer_list_model::emplace_clone_size_heatmap_layer(const std::shared_ptr<detection_result> &result) noexcept
{
	const auto head=this->layers_.size();
	this->insertRow(head);
	this->setData(this->index(head, 0), QVariant::fromValue(result));
}

void layer_list_model::select_layer_ptr(const QModelIndex &index) noexcept
{
	if(this->current_index_==index.row())
	{
		return;
	}
	this->current_index_=index.row();
	emit this->current_layer_changed(this->layers_[index.row()]);
}

bool layer_list_model::insertRows(const int row, const int count, const QModelIndex &parent) noexcept
{
	this->beginInsertRows(parent, row, row+count-1);
	for(int i=0; i<count; ++i)
	{
		this->layers_.insert(row, nullptr);
	}
	this->endInsertRows();
	return true;
}

bool layer_list_model::setData(const QModelIndex &index, const QVariant &value, int role) noexcept
{
	if(!index.isValid() || role!=Qt::EditRole || !value.canConvert<std::shared_ptr<detection_result>>())
	{
		return false;
	}

	this->layers_[index.row()]=std::make_shared<heatmap_layer>(value.value<std::shared_ptr<detection_result>>());
	emit dataChanged(index, index, {role});

	return true;
}

}

