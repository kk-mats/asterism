#include "grid_properties_widget.hpp"

namespace asterism
{

QWidget* grid_properties_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept
{
	if(grid_properties_model::is_base_selector(index) && index.model()->data(index, Qt::UserRole).canConvert<QPair<int, int>>())
	{
		auto *selector=new QComboBox(parent);
		QStringList r;
		const auto v=index.model()->data(index, Qt::UserRole).value<QPair<int, int>>();
		for(int i=0; i<v.first; ++i)
		{
			selector->addItem("["+QString::number(i)+"]", i);
		}
		selector->setCurrentIndex(v.second);
		connect(selector, qOverload<int>(&QComboBox::activated), this, &grid_properties_delegate::index_activated);
		return selector;
	}

	return QItemDelegate::createEditor(parent, option, index);
}

void grid_properties_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const noexcept
{
	if(grid_properties_model::is_base_selector(index))
	{
		auto *selector=qobject_cast<QComboBox *>(editor);
		if(const auto i=index.model()->data(index, Qt::EditRole).toInt(); i>=0)
		{
			selector->setCurrentIndex(i);
		}
		return;
	}

	QItemDelegate::setEditorData(editor, index);
}

void grid_properties_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const noexcept
{
	if(grid_properties_model::is_base_selector(index))
	{
		model->setData(index, qobject_cast<QComboBox *>(editor)->currentData(Qt::UserRole).toInt(), Qt::EditRole);
		return;
	}

	QItemDelegate::setModelData(editor, model, index);
}

void grid_properties_delegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem &option, const QModelIndex & index) const noexcept
{
	if(grid_properties_model::is_base_selector(index))
	{
		editor->setGeometry(option.rect);
		return;
	}
	QItemDelegate::updateEditorGeometry(editor, option, index);

}

void grid_properties_model::bind(const std::shared_ptr<matching_table>& matching_table) noexcept
{
	matching_table_=matching_table;
}

int grid_properties_model::rowCount(const QModelIndex &parent) const noexcept
{
	return this->vertical_header.size();
}

int grid_properties_model::columnCount(const QModelIndex &parent) const noexcept
{ 
	return std::max(1, this->horizontal_header.size());
}

QVariant grid_properties_model::data(const QModelIndex &index, int role) const noexcept
{
	if(!index.isValid() || this->responses_.size()==0)
	{
		return QVariant();
	}

	if(is_base_selector(index))
	{
		switch(role)
		{
			case Qt::UserRole: return QVariant::fromValue(qMakePair(this->base_.size(), this->current_));
			case Qt::EditRole: return this->current_;
			case Qt::DisplayRole: return "["+QString::number(this->current_)+"]";
		}
		return QVariant();
	}

	if(role==Qt::DisplayRole)
	{
		std::shared_ptr<clone_pair> p;
		const int c=index.column();
		int i=0;
		for(int acc=0; i<this->responses_.size(); ++i)
		{
			int width=this->responses_[i].size();
			if(width==0 && acc==c)
			{
				return index.row()==0 ? "None" : "";
			}
			if(acc<=c && c<acc+width)
			{
				p=this->responses_[i][c-acc];
				i=c-acc;
				break;
			}
			acc+=std::max(width, 1);
		}

		switch(index.row())
		{
			case 0: return "["+QString::number(i)+"]";
			case 1: return p->fragment1().begin();
			case 2: return p->fragment1().end();
			case 3: return p->fragment2().begin();
			case 4: return p->fragment2().end();
			case 5: return p->similarity();
		}
	}

	if(index.column()!=0 && index.row()!=0 && role==Qt::BackgroundRole)
	{
		std::shared_ptr<clone_pair> p;
		const int c=index.column();
		int i=1;
		for(int acc=1; i<this->responses_.size(); ++i)
		{
			int width=this->responses_[i].size();
			if(width==0 && acc==c)
			{
				return QVariant();
			}
			if(acc<=c && c<acc+width)
			{
				p=this->responses_[i][c-acc];
				i=c-acc;
				break;
			}
			acc+=std::max(width, 1);
		}

		if(!this->equals_to_base(p, index.row()))
		{
			return QColor(255, 128, 128);
		}
	}

	return QVariant();
}

bool grid_properties_model::setData(const QModelIndex &index, const QVariant &value, int role) noexcept
{
	if(index.row()==0 && index.column()==0 && role==Qt::EditRole && value.canConvert<int>())
	{
		this->change_current_index(value.toInt());
		return true;
	}

	return false;
}

QVariant grid_properties_model::headerData(int section, Qt::Orientation orientation, int role) const noexcept
{
	if(role!=Qt::DisplayRole)
	{
		return QVariant();
	}

	if(orientation==Qt::Vertical && section<this->vertical_header.size())
	{
		return this->vertical_header[section];
	}
	else if(section<this->horizontal_header.size())
	{
		return this->horizontal_header[section];
	}

	return QVariant();
}

Qt::ItemFlags grid_properties_model::flags(const QModelIndex & index) const noexcept
{
	if(index.row()==0 && index.column()==0)
	{
		return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	}

	return QAbstractItemModel::flags(index);
}

void grid_properties_model::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->primitive_=primitive;
	this->base_=(*primitive->clone_pair_layer())[grid_2d_coordinate::to_linear(file1->id(), file2->id())];
	this->change_current_index(0);
}

bool grid_properties_model::is_base_selector(const QModelIndex &index) noexcept
{
	return index.row()==0 && index.column()==0;
}

void grid_properties_model::activate_index(const int index) noexcept
{
	if(index!=this->current_)
	{
		this->change_current_index(index);
	}
}

bool grid_properties_model::change_current_index(const int index) noexcept
{
	if(index<this->base_.size())
	{
		this->current_=index;
		this->beginResetModel();
		this->horizontal_header.clear();

		const auto base=this->base_[index];
		this->responses_=matching_table_->matched_pair(query(this->primitive_, base));
		this->responses_.insert(this->responses_.begin(), response(this->primitive_, {base}));
		this->horizontal_header.append("Base <"+this->primitive_->environment().name()+">");;
		for(int i=1; i<this->responses_.size(); ++i)
		{
			const auto name=this->responses_[i].result()->environment().name();
			this->horizontal_header.append(name);
			for(int j=1; j<this->responses_[i].size(); ++j)
			{
				this->horizontal_header.append(name);
			}
		}

		this->endResetModel();
		return true;
	}

	return false;
}

bool grid_properties_model::equals_to_base(const std::shared_ptr<clone_pair>& p, const int row) const noexcept
{
	const auto base=this->base_[this->current_];
	switch(row)
	{
		case 1: return p->fragment1().begin()==base->fragment1().begin();
		case 2: return p->fragment1().end()==base->fragment1().end();
		case 3: return p->fragment2().begin()==base->fragment2().begin();
		case 4: return p->fragment2().end()==base->fragment2().end();
		case 5: return p->similarity()==base->similarity();
	}
	return false;
}



grid_properties_widget::grid_properties_widget(QWidget *parent) noexcept
	: QTableView(parent)
{
	this->setEditTriggers(QAbstractItemView::CurrentChanged);
	auto d=new grid_properties_delegate;
	connect(d, &grid_properties_delegate::index_activated, this->model_, &grid_properties_model::activate_index);
	this->setItemDelegateForRow(0, d);
	this->setModel(this->model_);
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void grid_properties_widget::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->model_->change_current_grid(file1, file2, primitive);
}

}