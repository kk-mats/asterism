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

bool layer_detail_model::setData(const QModelIndex &index, const QVariant &value, int role) noexcept
{
	if(!index.isValid() || role!=Qt::EditRole || index.row()!=0 || index.column()!=1 || !value.canConvert<QString>() || this->details_[0].second==value.toString())
	{
		return false;
	}
	emit result_name_input(value.toString());
	return true;
}

QVariant layer_detail_model::headerData(int, Qt::Orientation, int) const noexcept
{
	return QVariant();
}

Qt::ItemFlags layer_detail_model::flags(const QModelIndex &index) const noexcept
{
	auto f=QAbstractTableModel::flags(index);
	if(index.isValid() && index.row()==0 && index.column()==1)
	{
		f|=Qt::ItemIsEditable;
	}
	return f;
}


layer_detail_widget::layer_detail_widget(QWidget *parent) noexcept
	: QTableView(parent)
{
	this->setModel(this->model_);
	this->verticalHeader()->hide();
	this->horizontalHeader()->hide();
	this->horizontalHeader()->setStretchLastSection(true);

	connect(this->model_, &layer_detail_model::result_name_input, this, &layer_detail_widget::result_name_input);
}

void layer_detail_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->model_->beginResetModel();
	if(layer!=nullptr)
	{
		this->model_->current_=layer;
		this->model_->details_=layer->details();
	}
	else
	{
		this->model_->current_=nullptr;
		this->model_->details_.clear();
	}
	this->model_->endResetModel();
}

void layer_detail_widget::change_method(const int) noexcept
{
	this->model_->beginResetModel();
	this->model_->details_=this->model_->current_->details();
	this->model_->endResetModel();
}

void layer_detail_widget::change_result_name(const QString &name) noexcept
{
	this->model_->details_[0].second=name;
	const auto index=this->model_->index(0, 1);
	emit dataChanged(index, index);
}

}