#include "matched_clone_pair_list_widget.hpp"

namespace asterism
{

matched_list_model::item::item(const std::shared_ptr<clone_pair> &self, const QVariant &text, item *parent) noexcept
	: item(QVariant::fromValue(self), text, parent)
{
	auto *value=new item(tr("Value"), "", this);
	value->emplace_child(tr("Similarity"), self->similarity());
	auto *f1_item=new item(tr("Fragment1"), "", value);
	const auto f1=self->fragment1();
	f1_item->emplace_children({{tr("Path"), f1.file_ptr()->canonical_file_path()}, {tr("Begin"), f1.begin()}, {tr("End"), f1.end()}});
	value->append_child(f1_item);
	
	auto *f2_item=new item(tr("Fragment2"), "", value);
	const auto f2=self->fragment2();
	f2_item->emplace_children({{tr("Path"), f2.file_ptr()->canonical_file_path()}, {tr("Begin"), f2.begin()}, {tr("End"), f2.end()}});
	value->append_child(f2_item);

	this->children_.append(value);
}

matched_list_model::item::item(const std::shared_ptr<detection_result> &self, const QVariant &text, item *parent) noexcept
	: item(QVariant::fromValue(self), text, parent)
{}

matched_list_model::item::item(const QVariant &self, const QVariant &text, item *parent) noexcept
	: self_({self, text}), parent_(parent)
{}

matched_list_model::item::~item() noexcept
{
	qDeleteAll(this->children_);
}


int matched_list_model::item::row() const noexcept
{
	if(this->parent_!=nullptr)
	{
		auto i=this->parent_->children_.indexOf(const_cast<item *>(this));
		return i;
	}
	return 0;
	//return this->parent_!=nullptr ? this->parent_->children_.indexOf(const_cast<item *>(this)) : 0;
}

int matched_list_model::item::column_size() const noexcept
{
	return this->self_.size();
}

int matched_list_model::item::children_size() const noexcept
{
	return this->children_.size();
}

QVariant matched_list_model::item::self(const int i) const noexcept
{
	return this->self_[i];
}

matched_list_model::item *matched_list_model::item::parent() const noexcept
{
	return this->parent_;
}

matched_list_model::item* matched_list_model::item::child(const int i) const noexcept
{
	return this->children_.at(i);
}

void matched_list_model::item::append_child(item *i) noexcept
{
	this->children_.append(i);
}

void matched_list_model::item::emplace_child(const QVariant &child, const QVariant &text) noexcept
{
	this->children_.append(new item(child, text, this));
}

void matched_list_model::item::emplace_children(const QVector<std::pair<QVariant, QVariant>> &children) noexcept
{
	for(const auto &child:children)
	{
		this->children_.append(new item(child.first, child.second, this));
	}
}


QVariant matched_list_model::item::data(const int row, const int column) const noexcept
{
	if(this->is_clone_pair(column))
	{
		return tr("clone pair [")+QString::number(row)+"]";
	}
	if(this->is_detection_result(column))
	{
		return tr("In <")+this->to_detection_result(column)->environment().name()+">";
	}

	return this->self_[column];
}


bool matched_list_model::item::is_string(const int i) const noexcept
{
	return this->self_[i].canConvert<QString>();
}

bool matched_list_model::item::is_int(const int i) const noexcept
{
	return this->self_[i].canConvert<int>();
}

bool matched_list_model::item::is_clone_pair(const int i) const noexcept
{
	return this->self_[i].canConvert<std::shared_ptr<clone_pair>>();
}

bool matched_list_model::item::is_detection_result(const int i) const noexcept
{
	return this->self_[i].canConvert<std::shared_ptr<detection_result>>();
}

QString matched_list_model::item::to_string(const int i) const noexcept
{
	return this->self_[i].value<QString>();
}

int matched_list_model::item::to_int(const int i) const noexcept
{
	return this->self_[i].value<int>();
}

std::shared_ptr<clone_pair> matched_list_model::item::to_clone_pair(const int i) const noexcept
{
	return this->self_[i].value<std::shared_ptr<clone_pair>>();
}

std::shared_ptr<detection_result> matched_list_model::item::to_detection_result(const int i) const noexcept
{
	return this->self_[i].value<std::shared_ptr<detection_result>>();
}


matched_list_model::~matched_list_model() noexcept
{
	delete this->root_;
}

void matched_list_model::bind(const std::shared_ptr<matching_table> &matching_table) noexcept
{
	matching_table_=matching_table;
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
	if(orientation!=Qt::Horizontal || role!=Qt::DisplayRole)
	{
		return QVariant();
	}
	
	return this->root_->data(0, section);
}

int matched_list_model::rowCount(const QModelIndex &parent) const noexcept
{
	if(parent.column()>0)
	{
		return 0;
	}
	item *parent_item=parent.isValid() ? static_cast<item *>(parent.internalPointer()) : this->root_;
	return parent_item->children_size();
}

int matched_list_model::columnCount(const QModelIndex &parent) const noexcept
{
	return 2;
}

QModelIndex matched_list_model::index(int row, int column, const QModelIndex &parent) const noexcept
{
	if(this->hasIndex(row, column, parent))
	{
		item *parent_item=parent.isValid() ? static_cast<item *>(parent.internalPointer()) : this->root_;
		item *child_item=parent_item->child(row);

		if(child_item!=nullptr && column<child_item->column_size())
		{
			return this->createIndex(row, column, child_item);
		}
	}

	return QModelIndex();
}

QModelIndex matched_list_model::parent(const QModelIndex &index) const noexcept
{
	if(!index.isValid())
	{
		return QModelIndex();
	}

	item *child_item=static_cast<item *>(index.internalPointer());
	item *parent_item=child_item->parent();
	
	return parent_item!=this->root_ ? this->createIndex(parent_item->row(), 0, parent_item) : QModelIndex();
}

void matched_list_model::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->beginResetModel();
	delete this->root_;
	this->root_=new item(tr(""), "Description", nullptr);

	for(const auto &p:(*primitive->clone_pair_layer())[grid_2d_coordinate::to_linear(file1->id(), file2->id())])
	{
		item *top_item=new item(p, "", this->root_);

		for(const auto &r:matching_table_->matched_pair(query(primitive, p)))
		{
			item *result_item=new item(r.result(), QString::number(r.size())+" matched", top_item);

			for(const auto &mp:r)
			{
				item *mp_item=new item(mp, "", result_item);
				result_item->append_child(mp_item);
			}
			top_item->append_child(result_item);
		}
		this->root_->append_child(top_item);
	}

	this->endResetModel();
}

void matched_list_model::update() noexcept
{
	this->beginResetModel();
	this->endResetModel();
}

matched_list_widget::matched_list_widget(QWidget *parent)
	: QTreeView(parent)
{
	this->setModel(this->model_);
	this->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	this->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

matched_list_widget::~matched_list_widget()
{
}

void matched_list_widget::change_result_name() noexcept
{
	this->model_->update();
}

}