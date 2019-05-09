#include "layer_detail_widget.hpp"

namespace asterism
{

layer_detail_model::layer_detail_model(QObject *parent) noexcept
	: QAbstractTableModel(parent)
{}

int layer_detail_model::rowCount(const QModelIndex &) const noexcept
{
	return this->details_.size();
}

int layer_detail_model::columnCount(const QModelIndex &) const noexcept
{
	return 2;
}

QVariant layer_detail_model::data(const QModelIndex &index, int role) const noexcept
{
	if(!index.isValid() || role!=Qt::DisplayRole)
	{
		return QVariant();
	}

	switch(index.column())
	{
		case 0:
		{
			return this->details_[index.row()].first;
		}
		case 1:
		{
			return this->details_[index.row()].second;
		}
	}

	return QVariant();
}

QVariant layer_detail_model::headerData(int, Qt::Orientation, int) const noexcept
{
	return QVariant();
}


layer_detail_widget::layer_detail_widget(QWidget *parent) noexcept
	: QTableView(parent)
{
	this->setModel(this->model_);
	this->verticalHeader()->hide();
	this->horizontalHeader()->hide();
	this->horizontalHeader()->setStretchLastSection(true);
}

void layer_detail_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->model_->beginResetModel();
	this->model_->current_=layer;
	this->model_->details_=layer->details();
	this->model_->endResetModel();
}

void layer_detail_widget::change_method(const int) noexcept
{
	this->model_->beginResetModel();
	this->model_->details_=this->model_->current_->details();
	this->model_->endResetModel();
}

}