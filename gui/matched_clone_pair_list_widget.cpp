#include "matched_clone_pair_list_widget.hpp"

namespace asterism
{

matched_list_model::item::~item() noexcept
{
	qDeleteAll(this->children_);
}


int matched_list_model::item::row() const noexcept
{
	return this->parent_!=nullptr ? this->parent_->children_.indexOf(const_cast<item *>(this)) : 0;
}

QVariant matched_list_model::item::data(const int row, const int column) const noexcept
{
	if(this->self_.canConvert<std::shared_ptr<clone_pair>>())
	{
		return this->self_.value<std::shared_ptr<clone_pair>>()->string();
	}
	else if(this->self_.canConvert<std::shared_ptr<detection_result>>())
	{
		return this->self_.value<std::shared_ptr<detection_result>>()->environment().name();
	}

	return QVariant();
}

matched_list_model::~matched_list_model() noexcept
{
	delete this->root_;
}

void matched_list_model::bind(const std::shared_ptr<file_index> &file_table, const std::shared_ptr<matching_table> &matching_table) noexcept
{
	matching_table_=matching_table;
	file_index_=file_table;
}

QVariant matched_list_model::data(const QModelIndex &index, int role) const noexcept
{
	if(!index.isValid() || role!=Qt::DisplayRole)
	{
		return QVariant();
	}

	return static_cast<item *>(index.internalPointer())->data(index.row(), index.column());	
}

Qt::ItemFlags matched_list_model::flags(const QModelIndex &index) const noexcept
{
	return index.isValid() ? QAbstractItemModel::flags(index) : 0;
}

QVariant matched_list_model::headerData(int section, Qt::Orientation orientation, int role) const noexcept
{
	if(orientation==Qt::Horizontal && role==Qt::DisplayRole)
	{
		return QStringLiteral("Matched Clone Pair");
	}
	return QVariant();
}

int matched_list_model::rowCount(const QModelIndex &parent) const noexcept
{
	if(parent.column()>0)
	{
		return 0;
	}
	item *parent_item=parent.isValid() ? static_cast<item *>(parent.internalPointer()) : this->root_;

	return parent_item->children_.size();
}

int matched_list_model::columnCount(const QModelIndex &parent) const noexcept
{
	return 1;
}

QModelIndex matched_list_model::index(int row, int column, const QModelIndex &parent) const noexcept
{
	if(!this->hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	item *parent_item=parent.isValid() ? static_cast<item *>(parent.internalPointer()) : this->root_;
	item *child_item=parent_item->children_[row];

	return child_item!=nullptr ? this->createIndex(row, column, child_item) : QModelIndex();
}

QModelIndex matched_list_model::parent(const QModelIndex &index) const noexcept
{
	if(!index.isValid())
	{
		return QModelIndex();
	}

	item *child_item=static_cast<item *>(index.internalPointer());
	item *parent_item=child_item->parent_;

	if(parent_item==this->root_)
	{
		return QModelIndex();
	}

	return this->createIndex(parent_item->row(), 0, parent_item);
}

void matched_list_model::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->beginResetModel();
	delete this->root_;
	this->root_=new item;

	for(const auto &p:(*primitive->clone_pair_layer())[grid_2d_coordinate::to_linear(file_index_->at(file1), file_index_->at(file2))])
	{
		item *top_item=new item;
		top_item->parent_=this->root_;
		top_item->self_.setValue(p);

		for(const auto &r:matching_table_->matched_pair(primitive, p, file_index_))
		{
			item *result_item=new item;
			result_item->parent_=top_item;
			result_item->self_.setValue(r.first);

			for(const auto &mp:r.second)
			{
				item *mp_item=new item;
				mp_item->parent_=result_item;
				mp_item->self_.setValue(mp);
				result_item->children_.append(mp_item);
			}
			top_item->children_.append(result_item);
		}
		this->root_->children_.append(top_item);
	}

	this->endResetModel();
	return;
}

matched_list_widget::matched_list_widget(QWidget *parent)
	: QTreeView(parent)
{
	this->setModel(this->model_);
}

matched_list_widget::~matched_list_widget()
{
}

}