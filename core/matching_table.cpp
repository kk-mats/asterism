#include "matching_table.hpp"

namespace asterism
{

matching_table::key::key(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept
	: r_(std::minmax(left, right))
{}

bool matching_table::unit::better(const float ok_v, const float good_v, QPair<float, float> &&ok_good_max, const float t) const noexcept
{
	return (good_v>=t && good_v>=ok_good_max.second) || (qFuzzyCompare(good_v, ok_good_max.second) && ok_v>ok_good_max.first) || (ok_v>=t && ok_good_max.first<t);
}

std::unordered_map<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>> matching_table::unit::map_unidirectionally(const shared_vector<clone_pair> &g1, const shared_vector<clone_pair> &g2) const noexcept
{
	std::unordered_map<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>> matched;

	for(const auto &r:g1)
	{
		for(const auto &c:g2)
		{
			auto ok_good_max=matched.find(r)!=matched.end() ? qMakePair(ok(c, matched[r]), good(c, matched[r])) : qMakePair(threshold_, threshold_);
			auto ok_v=ok(c, r);
			auto good_v=good(c, r);

			if(this->better(ok_v, good_v, std::move(ok_good_max), threshold_))
			{
				matched[c]=r;
			}
		}
	}

	return matched;
}

void matching_table::unit::map_mutually(const shared_vector<clone_pair> &left, const shared_vector<clone_pair> &right) noexcept
{
	auto left_right=this->map_unidirectionally(left, right);
	auto right_left=this->map_unidirectionally(right, left);
	
	for(const auto &e:left_right)
	{
		this->matching_list_.push_back(e);
	}

	for(const auto &e:right_left)
	{
		this->matching_list_.emplace_back(e.second, e.first);
	}

	std::sort(this->matching_list_.begin(), this->matching_list_.end());
	std::unique()
}


}
