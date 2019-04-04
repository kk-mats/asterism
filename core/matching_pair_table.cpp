#include "matching_pair_table.hpp"

namespace asterism
{

matching_pair_table::matching_pair_table(const detection_result &left, const detection_result &right, const float t) noexcept
	: left_result_id_(left.id()), right_result_id_(right.id()), matching_list_(this->bidirectional_matching(left, right, t))
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

bool matching_pair_table::better(const float ok_v, const float ok_max, const float good_v, const float good_max, const float t) const noexcept
{
	return (good_v>=t && good_v>=good_max) || (good_v==good_max && ok_v>ok_max) || (ok_v>=t && ok_max<t);
}

QVector<QPair<clone_pair::id_t, clone_pair::id_t>> matching_pair_table::unidirectional_matching(const detection_result &first, const detection_result &second, const float t) const noexcept
{
	QHash<clone_pair, clone_pair> matched;

	for(auto i=first.clone_pair_layer().begin1d(), end=first.clone_pair_layer().end1d(); i!=end; ++i)
	{
		const auto &pairs_first=first.clone_pair_layer()[i];
		const auto &pairs_second=second.clone_pair_layer()[i];

		for(const auto &r:pairs_first)
		{
			for(const auto &c:pairs_second)
			{
				if(matched.contains(r))
				{
					auto ok_max=ok(c, matched[r]);
					auto good_max=good(c, matched[r]);
					auto ok_v=ok(c, r);
					auto good_v=good(c, r);

					if(this->better(ok_v, ok_max, good_v, good_max, t))
					{
						matched[c]=r;
					}
				}
				else
				{
					matched[r]=c;
				}
			}
		}
	}

	QVector<QPair<clone_pair::id_t, clone_pair::id_t>> r;
	for(auto &&key:matched.keys())
	{
		r.push_back(qMakePair(key.id(), matched[key].id()));
	}

	return r;
}

QVector<QPair<clone_pair::id_t, clone_pair::id_t>> matching_pair_table::bidirectional_matching(const detection_result &left, const detection_result &right, const float t) const noexcept
{
	auto left_right=this->unidirectional_matching(left, right, t);
	auto right_left=this->unidirectional_matching(right, left, t);
	std::for_each(right_left.begin(), right_left.end(), [](auto &&e){std::swap(e.first, e.second);});

	left_right.append(std::move(right_left));
	std::sort(left_right.begin(), left_right.end(), [](const auto &e1, const auto &e2){ return e1.first==e2.first ? e1.second<e2.second : e1.first<e2.first;});
	left_right.erase(std::unique(left_right.begin(), left_right.end()), left_right.end());
	return left_right;
}

}
