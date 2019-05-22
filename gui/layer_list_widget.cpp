#include "layer_list_widget.hpp"

namespace asterism
{

layer_list_model::layer_list_model(QObject *parent) noexcept
	: QAbstractListModel(parent)
{}

bool layer_list_model::removeRows(int row, int count, const QModelIndex &parent)
{
	this->beginRemoveRows(parent, row, row+count-1);
	for(int i=0; i<count; ++i)
	{
		this->layers_.removeAt(row);
	}
	this->endRemoveRows();
	return true;
}

int layer_list_model::rowCount(const QModelIndex &) const
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

bool layer_list_model::has_conflict(const QString &name) const noexcept
{
	for(const auto &h:this->layers_)
	{
		if(h->name()==name)
		{
			return true;
		}
	}
	return false;
}

bool layer_list_model::setData(const QModelIndex &index, const QVariant &value, int role) noexcept
{
	if(!index.isValid() || role!=Qt::EditRole)
	{
		return false;
	}

	if(value.canConvert<QString>())
	{
		return this->change_result_name(value.toString());
	}
	else if(value.canConvert<std::shared_ptr<detection_result>>())
	{
		this->layers_[index.row()]=std::make_shared<heatmap_layer>(value.value<std::shared_ptr<detection_result>>(), heatmap_layer::method::clone_pair_size());
		emit dataChanged(index, index, {role});
		return true;
	}
	return false;
}

Qt::ItemFlags layer_list_model::flags(const QModelIndex &index) const noexcept
{
	auto f=QAbstractListModel::flags(index);
	if(index.isValid())
	{
		f|=Qt::ItemIsEditable;
	}
	return f;
}

bool layer_list_model::change_result_name(const QString &name) noexcept
{
	if(auto &result=this->layers_[this->current_index_]; !name.isEmpty() && result->name()!=name && !this->has_conflict(name))
	{
		result->set_name(name);
		emit result_name_changed(name);
		return true;
	}
	return false;
}

layer_list_widget::layer_list_widget(QWidget *parent) noexcept
	: QListView(parent)
{
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	this->setModel(this->model_);

	connect(this, &layer_list_widget::clicked, this, &layer_list_widget::select_layer_ptr);
	connect(this, &layer_list_widget::customContextMenuRequested, this, &layer_list_widget::show_context_menu);
	connect(this->model_, &layer_list_model::result_name_changed, this, &layer_list_widget::result_name_changed);
}

void layer_list_widget::update_layers() noexcept
{
	for(auto &&h:this->model_->layers_)
	{
		h->update();
	}
}

void layer_list_widget::set_clone_size_heatmap_layers(const shared_list<detection_result> &results) noexcept
{
	if(auto size=this->model_->rowCount(); size>0)
	{
		this->model_->removeRows(0, size);
	}
	this->emplace_clone_size_heatmap_layers(results);
}


void layer_list_widget::emplace_clone_size_heatmap_layers(const shared_list<detection_result> &results) noexcept
{
	const auto head=this->model_->layers_.size();
	this->model_->insertRows(head, results.size());
	for(auto i=0; i<results.size(); ++i)
	{
		this->model_->setData(this->model_->index(head+i, 0), QVariant::fromValue(results[i]));
	}
}

void layer_list_widget::emplace_clone_size_heatmap_layer(const std::shared_ptr<detection_result> &result) noexcept
{
	const auto head=this->model_->layers_.size();
	this->model_->insertRow(head);
	this->model_->setData(this->model_->index(head, 0), QVariant::fromValue(result));
}

void layer_list_widget::select_layer_ptr(const QModelIndex &index) noexcept
{
	if(this->model_->current_index_==index.row())
	{
		return;
	}
	this->model_->current_index_=index.row();
	emit this->current_layer_changed(this->model_->layers_[index.row()]);
}

void layer_list_widget::show_context_menu(const QPoint &pos) noexcept
{
	QMenu *cm_=new QMenu;
	QAction *rename_act_=cm_->addAction("Rename", this, &layer_list_widget::click_rename);
	QAction *remove_act_=cm_->addAction("Remove", this, &layer_list_widget::click_remove);
	rename_act_->setStatusTip(tr("Rename Detection Result"));
	remove_act_->setStatusTip(tr("Remove Detection Result"));
	cm_->exec(this->mapToGlobal(pos));
}

void layer_list_widget::click_rename() noexcept
{
	auto i=this->currentIndex().row();
}

void layer_list_widget::click_remove() noexcept
{
	auto i=this->currentIndex().row();
	const auto ptr=this->model_->layers_[i]->primitive();
	this->model_->removeRow(i);

	emit remove(ptr);

	const auto size=this->model_->layers_.size();
	if(size!=0)
	{
		this->model_->current_index_=i<size ? i : size-1;
		emit current_layer_changed(this->model_->layers_[this->model_->current_index_]);
	}
	else
	{
		this->model_->current_index_=-1;
		emit current_layer_changed(nullptr);
	}
	
}

void layer_list_widget::change_result_name(const QString &name) noexcept
{
	if(this->model_->change_result_name(name))
	{
		emit dataChanged(this->currentIndex(), this->currentIndex());
	}
}

}