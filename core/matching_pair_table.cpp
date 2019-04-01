#include "matching_pair_table.hpp"

namespace asterism
{

matching_pair_table::matching_pair_table(const clone_pair_grid_layer &left, const clone_pair_grid_layer &right) noexcept
	: left_result_id_(left.result_id()), right_result_id_(right.result_id()), matching_list_(this->bidirectional_matching(left, right))
{}

std::optional<clone_pair::id_t> matching_pair_table::has_left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept
{
	return this->count_left_clone_pair_of(right_clone_pair_id)>0;
}

std::optional<clone_pair::id_t> matching_pair_table::has_right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept
{
	return this->count_right_clone_pair_of(left_clone_pair_id)>0;
}

int matching_pair_table::count_left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept
{
	return std::count_if(this->matching_list_.begin(), this->matching_list_.end(), [&right_clone_pair_id](const auto &m)
	{
		return m.second==right_clone_pair_id;
	});
}

int matching_pair_table::count_right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept
{
	return std::count_if(this->matching_list_.begin(), this->matching_list_.end(), [&left_clone_pair_id](const auto &m)
	{
		return m.first==left_clone_pair_id;
	});
}

detection_result::id_t matching_pair_table::left_result_id() const noexcept
{
	return this->left_result_id_;
}

detection_result::id_t matching_pair_table::right_result_id() const noexcept
{
	return this->right_result_id_;
}

QVector<clone_pair::id_t> matching_pair_table::left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept
{
	QVector<clone_pair::id_t> r;
	for(const auto &p:this->matching_list_)
	{
		if(p.second==right_clone_pair_id)
		{
			r.push_back(p.first);
		}
	}

	return r;
}

QVector<clone_pair::id_t> matching_pair_table::right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept
{
	QVector<clone_pair::id_t> r;
	for(const auto &p:this->matching_list_)
	{
		if(p.first==left_clone_pair_id)
		{
			r.push_back(p.second);
		}
	}

	return r;
}

QList<QPair<clone_pair::id_t, clone_pair::id_t>> matching_pair_table::unidirectional_matching(const clone_pair_grid_layer &first, const clone_pair_grid_layer &second) const noexcept
{
	for(auto i=first.begin1d(), end=first.end1d(); i!=end; ++i)
	{
		const auto &pairs_first=first[i];
		const auto &pairs_second=second[i];
	}
}

QVector<QPair<clone_pair::id_t, clone_pair::id_t>> matching_pair_table::bidirectional_matching(const clone_pair_grid_layer &left, const clone_pair_grid_layer &right) const noexcept
{
	auto left_right=this->unidirectional_matching(left, right);
	auto right_left=this->unidirectional_matching(right, left);
	std::for_each(right_left.begin(), right_left.end(), [](auto &&e){std::swap(e.first, e.second);});

	left_right.append(std::move(right_left));
	auto r=left_right.toVector();
	std::sort(r.begin(), r.end(), [](const auto &e1, const auto &e2){ return e1.first==e2.first ? e1.second<e2.second : e1.first<e2.first;});
	r.erase(std::unique(r.begin(), r.end()), r.end());
	return r;
}

}
