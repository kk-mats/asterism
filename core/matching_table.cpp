#include "matching_table.hpp"

namespace asterism
{

matching_table_unit::matching_table_unit() noexcept
{}

matching_table_unit::matching_table_unit(const detection_result &left, const detection_result &right, const float t) noexcept
	: left_result_id_(left.id()), right_result_id_(right.id()), matching_list_(this->bidirectional_matching(left, right, t))
{}

std::optional<clone_pair::id_t> matching_table_unit::has_left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept
{
	return this->count_left_clone_pair_of(right_clone_pair_id)>0;
}

std::optional<clone_pair::id_t> matching_table_unit::has_right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept
{
	return this->count_right_clone_pair_of(left_clone_pair_id)>0;
}

int matching_table_unit::count_left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept
{
	return std::count_if(this->matching_list_.begin(), this->matching_list_.end(), [&right_clone_pair_id](const auto &m)
	{
		return m.second==right_clone_pair_id;
	});
}

int matching_table_unit::count_right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept
{
	return std::count_if(this->matching_list_.begin(), this->matching_list_.end(), [&left_clone_pair_id](const auto &m)
	{
		return m.first==left_clone_pair_id;
	});
}

detection_result::id_t matching_table_unit::left_result_id() const noexcept
{
	return this->left_result_id_;
}

detection_result::id_t matching_table_unit::right_result_id() const noexcept
{
	return this->right_result_id_;
}

QVector<clone_pair::id_t> matching_table_unit::left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept
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

QVector<clone_pair::id_t> matching_table_unit::right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept
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

bool matching_table_unit::better(const float ok_v, const float good_v, QPair<float, float> &&ok_good_max, const float t) const noexcept
{
	return (good_v>=t && good_v>=ok_good_max.second) || (qFuzzyCompare(good_v, ok_good_max.second) && ok_v>ok_good_max.first) || (ok_v>=t && ok_good_max.first<t);
}

QVector<QPair<clone_pair::id_t, clone_pair::id_t>> matching_table_unit::unidirectional_matching(const detection_result &first, const detection_result &second, const float t) const noexcept
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
				auto ok_good_max=matched.contains(r) ? qMakePair(ok(c, matched[r]), good(c, matched[r])) : qMakePair(t, t);
				auto ok_v=ok(c, r);
				auto good_v=good(c, r);

				if(this->better(ok_v, good_v, std::move(ok_good_max), t))
				{
					matched[c]=r;
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

QVector<QPair<clone_pair::id_t, clone_pair::id_t>> matching_table_unit::bidirectional_matching(const detection_result &left, const detection_result &right, const float t) const noexcept
{
	auto left_right=this->unidirectional_matching(left, right, t);
	auto right_left=this->unidirectional_matching(right, left, t);
	std::for_each(right_left.begin(), right_left.end(), [](auto &&e){std::swap(e.first, e.second);});

	left_right.append(std::move(right_left));
	std::sort(left_right.begin(), left_right.end(), [](const auto &e1, const auto &e2){ return e1.first==e2.first ? e1.second<e2.second : e1.first<e2.first;});
	left_right.erase(std::unique(left_right.begin(), left_right.end()), left_right.end());
	return left_right;
}


matching_table::key::key(const detection_result::id_t &key1, const detection_result::id_t &key2) noexcept
	: key1_(key1), key2_(key2)
{};

matching_table::key::key(const std::pair<detection_result::id_t, detection_result::id_t> &key) noexcept
	: key1_(key.first), key2_(key.second)
{}

bool matching_table::key::operator ==(const key &other) const noexcept
{
	return (this->key1_==other.key1_ && this->key2_==other.key2_) || (this->key1_==other.key2_ && this->key2_==other.key2_);
}

bool matching_table::map_mutually(const QHash<detection_result::id_t, detection_result> &detection_results, const QList<detection_result::id_t> &target_ids) noexcept
{
	for(auto &&key1:target_ids)
	{
		for(auto &&key2:target_ids)
		{

			if(!detection_results.contains(key1) || !detection_results.contains(key2))
			{
				qCritical()<<reference_error::missing_detection_result_id;
				return false;
			}

			if(key1==key2 || this->units_.contains({key1, key2}))
			{
				continue;
			}

			this->units_.insert({key1, key2}, matching_table_unit(detection_results[key1], detection_results[key2], this->threshold_));
		}
	}

	return target_ids.size()!=1;
}

const matching_table_unit matching_table::operator [](const key &key) const noexcept
{
	return this->units_.value(key);
}

matching_table_unit& matching_table::operator [](const key &key) noexcept
{
	return this->units_[key];
}

void matching_table::set_threshold(const float threshold, const QHash<detection_result::id_t, detection_result> &detection_results) noexcept
{
	this->threshold_=threshold;
	this->map_mutually(detection_results, detection_results.keys());
}

uint qHash(const matching_table::key &key, uint seed) noexcept
{
	return uint(key.key1_)^seed+uint(key.key2_);
}

}
