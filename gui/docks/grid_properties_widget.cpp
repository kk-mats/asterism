#include "grid_properties_widget.hpp"

namespace asterism
{
grid_properties_delegate::grid_properties_delegate(const int size, QWidget *parent) noexcept
	: n_(size)
{}

QWidget* grid_properties_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept
{
	if(index.row()==0 && index.column()==0)
	{
		auto *selector=new QComboBox(parent);
		for(int i=0; i<this->n_; ++i)
		{
			selector->addItem("["+QString::number(i)+"]");
		}
		connect(selector, qOverload<int>(&QComboBox::currentIndexChanged), this, &grid_properties_delegate::index_changed);
		return selector;
	}

	return QItemDelegate::createEditor(parent, option, index);
}

void grid_properties_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const noexcept
{
	if(index.row()==0 && index.column()==0)
	{
		auto *selector=qobject_cast<QComboBox *>(editor);
		selector
	}
	QItemDelegate::setEditorData(editor, index);
}

void grid_properties_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const noexcept
{
	QItemDelegate::setModelData(editor, model, index);
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
	return this->horizontal_header.size();
}

QVariant grid_properties_model::data(const QModelIndex &index, int role) const noexcept
{
	if(role!=Qt::DisplayRole && !index.isValid())
	{
		return QVariant();
	}

	std::shared_ptr<clone_pair> p;
	if(index.column()==0)
	{
		p=this->base_[0].body();
	}
	else
	{
		const int r=index.row();
		for(int i=1, acc=1; i<this->others_.size(); ++i)
		{
			int width=this->others_[i-1].size();
			if(acc<=r && r<acc+width)
			{
				p=this->others_[i-1][r-acc];
			}
		}
	}
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



}