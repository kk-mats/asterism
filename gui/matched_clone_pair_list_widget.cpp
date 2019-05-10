#include "matched_clone_pair_list_widget.hpp"

namespace asterism
{

matched_list_widget::matched_list_widget(QWidget *parent)
	: QTreeView(parent)
{
	this->setModel(this->model_);
}

matched_list_widget::~matched_list_widget()
{
}

void matched_list_model::bind(const std::shared_ptr<file_index> &file_table, const std::shared_ptr<matching_table> &matching_table) noexcept
{
	matching_table_=matching_table;
	file_index_=file_table;
}

QVariant matched_list_model::data(const QModelIndex &index, int role) const noexcept
{
	if(role==Qt::DisplayRole && index.isValid())
	{
		if(index.data().canConvert<top_clone_pair>())
		{
			return index.data().value<top_clone_pair>().self_->string();
		}

		if(index.data().canConvert<result_category>())
		{
			const auto t=index.data().value<result_category>().self_;
			return "name="+t->environment().name()+", source="+t->environment().source();
		}

		if(index.data().canConvert<std::shared_ptr<clone_pair>>())
		{
			return index.data().value<std::shared_ptr<clone_pair>>()->string();
		}

		if(index.data().canConvert<fragment>())
		{
			return index.data().value<fragment>().string();
		}
	}

	return QVariant();
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
	if(!parent.isValid())
	{
		return this->matched_clone_pair_.size();
	}
	
	if(parent.data().canConvert<top_clone_pair>())
	{
		return parent.data().value<top_clone_pair>().children_.size();
	}
	/*
	if(parent.data().canConvert<result_category>())
	{
		return parent.data().value<result_category>().children_.size();
	}

	if(parent.data().canConvert<std::shared_ptr<clone_pair>>())
	{
		// clone_pair.fragment1, clone_pair.fragment2 and clone_pair.similarity 
		return 2;
	}
	*/
	return 0;
}

int matched_list_model::columnCount(const QModelIndex &parent) const noexcept
{
	if(parent.data().canConvert<std::shared_ptr<clone_pair>>())
	{
		// clone_pair.fragment1, clone_pair.fragment2 and clone_pair.similarity 
		return 1;
	}
	return 1;
}

QModelIndex matched_list_model::index(int row, int column, const QModelIndex &parent) const noexcept
{
	if(!parent.isValid())
	{
		if(column==0 && row<this->matched_clone_pair_.size())
		{
			return this->createIndex(row, 0, (void *)&this->matched_clone_pair_[row]);
		}

		return QModelIndex();
	}

	if(parent.data().canConvert<top_clone_pair>())
	{
		const auto &t=parent.data().value<top_clone_pair>().children_;
		return row<t.size() ? this->createIndex(row, 0, (void *)&t[row]) : QModelIndex();
	}

	if(parent.data().canConvert<result_category>())
	{
		const auto &t=parent.data().value<result_category>().children_;
		return row<t.size() ? this->createIndex(row, 0, (void*)&t[row]) : QModelIndex();
	}

	if(parent.data().canConvert<std::shared_ptr<clone_pair>>() && column==1)
	{
		const auto &t=parent.data().value<std::shared_ptr<clone_pair>>();
		switch(row)
		{
			case 0: return this->createIndex(row, 0, &t->fragment1());
			case 1: return this->createIndex(row, 1, &t->fragment2());
		}
	}
	return QModelIndex();
}

QModelIndex matched_list_model::parent(const QModelIndex &index) const noexcept
{
	if(index.isValid())
	{
		if(index.data().canConvert<result_category>())
		{
			const auto t=index.data().value<result_category>();
			for(int r=0; r<this->matched_clone_pair_.size(); ++r)
			{
				if(this->matched_clone_pair_[r].children_.indexOf(t)>-1)
				{
					return this->createIndex(r, 0, (void *)&this->matched_clone_pair_[r]);
				}
			}
		}
		else if(index.data().canConvert<std::shared_ptr<clone_pair>>())
		{
			const auto t=index.data().value<std::shared_ptr<clone_pair>>();
			for(const auto &top:this->matched_clone_pair_)
			{
				for(int r=0; r<top.children_.size(); ++r)
				{
					if(top.children_[r].children_.indexOf(t)>-1)
					{
						return this->createIndex(r, 0, (void *)&top.children_[r]);
					}
				}
			}
		}
	}
	return QModelIndex();
}

bool matched_list_model::result_category::operator==(const result_category &other) const noexcept
{
	return this->self_==other.self_;
}

void matched_list_model::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->matched_clone_pair_.clear();
	for(const auto &p:(*primitive->clone_pair_layer())[grid_2d_coordinate::to_linear(file_index_->at(file1), file_index_->at(file2))])
	{
		auto rr=matching_table_->matched_pair(primitive, p, file_index_);
		top_clone_pair top;
		top.self_=p;
		for(const auto &r:rr)
		{
			result_category rc;
			rc.self_=r.first;
			rc.children_=r.second;
			top.children_.push_back(rc);
		}
		this->matched_clone_pair_.push_back(top);
	}

	return;
}

}