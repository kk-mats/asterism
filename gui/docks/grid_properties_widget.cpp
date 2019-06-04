#include "grid_properties_widget.hpp"

namespace asterism
{

QWidget* grid_properties_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept
{
	if(index.row()==0 && index.column()==0)
	{
		auto *selector=new QComboBox(parent);
		for(const auto &s:index.data(Qt::UserRole).toStringList())
		{
			selector->addItem(s);
		}
		selector->setCurrentIndex(0);
		selector->setFrame(false);
		connect(selector, qOverload<int>(&QComboBox::activated), this, &grid_properties_delegate::remove_editor);
		return selector;
	}

	return QStyledItemDelegate::createEditor(parent, option, index);
}

void grid_properties_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const noexcept
{
	if(index.row()==0 && index.column()==0)
	{
		auto *selector=qobject_cast<QComboBox *>(editor);
		if(const auto i=selector->findText(index.data(Qt::EditRole).toString()); i>=0)
		{
			selector->setCurrentIndex(i);
		}
		return;
	}
	QStyledItemDelegate::setEditorData(editor, index);
}

void grid_properties_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const noexcept
{
	if(index.row()==0 && index.column()==0)
	{
		model->setData(index, qobject_cast<QComboBox *>(editor)->currentText(), Qt::EditRole);
		return;
	}
	QStyledItemDelegate::setModelData(editor, model, index);
}

QSize grid_properties_delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept
{
	return QStyledItemDelegate::sizeHint(option, index);
}

void grid_properties_delegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	editor->setGeometry(option.rect);
}

void grid_properties_delegate::remove_editor(const int index) noexcept
{
	auto *selector=qobject_cast<QComboBox *>(this->sender());
	//emit commitData(selector);
	//emit closeEditor(selector);
	if(this->previous_!=index)
	{
		this->previous_=index;
		emit index_changed(index);
	}
}

void grid_properties_model::bind(const std::shared_ptr<matching_table>& matching_table) noexcept
{
	matching_table_=matching_table;
}

int grid_properties_model::rowCount(const QModelIndex &parent) const noexcept
{
	return this->vertical_header.size();
}

int grid_properties_model::columnCount(const QModelIndex & parent) const noexcept
{ 
	return std::max(1, this->horizontal_header.size());
}

QVariant grid_properties_model::data(const QModelIndex &index, int role) const noexcept
{
	if(!index.isValid() || this->responses_.size()==0)
	{
		return QVariant();
	}

	if(index.row()==0 && index.column()==0)
	{
		if(Qt::UserRole)
		{
			QStringList r;
			for(int i=0; i<this->base_.size(); ++i)
			{
				r<<"["+QString::number(i)+"]";
			}
			return r;
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

	return QVariant();
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

void grid_properties_model::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->primitive_=primitive;
	this->base_=(*primitive->clone_pair_layer())[grid_2d_coordinate::to_linear(file1->id(), file2->id())];
	this->change_current_index(0);
}

void grid_properties_model::change_current_index(const int index) noexcept
{
	this->beginResetModel();
	this->horizontal_header.clear();
	if(index<this->base_.size())
	{
		this->current_=this->base_[index];
		this->responses_=matching_table_->matched_pair(query(this->primitive_, this->current_));
		this->responses_.insert(this->responses_.begin(), response(this->primitive_, {this->current_}));
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
	}
	else
	{
		this->responses_.clear();
	}
	this->endResetModel();
}



grid_properties_widget::grid_properties_widget(QWidget *parent) noexcept
	: QTableView(parent)
{
	//this->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
	this->setModel(this->model_);
	this->setItemDelegateForRow(0, this->grid_properties_delegate_);
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	connect(this->grid_properties_delegate_, &grid_properties_delegate::index_changed, this->model_, &grid_properties_model::change_current_index);
}

void grid_properties_widget::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->model_->change_current_grid(file1, file2, primitive);
}

}