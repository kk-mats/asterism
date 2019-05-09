#include "matching_table.hpp"

namespace asterism
{

std::size_t matching_table::key::hash::operator()(const key &key) const noexcept
{
	return qHash((key.left()->environment().source()))+qHash(key.right()->environment().source());
}

matching_table::key::key(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept
	: r_(std::minmax(left, right))
{}

std::shared_ptr<detection_result> matching_table::key::left() const noexcept
{
	return this->r_.first;
}

std::shared_ptr<detection_result> matching_table::key::right() const noexcept
{
	return this->r_.second;
}

bool matching_table::key::operator==(const key &other) const noexcept
{
	return this->r_==other.r_;
}


matching_table::unit::unit(const key &key) noexcept
	: key_(key)
{
	this->update();
}

int matching_table::unit::count_matching_pair(const std::shared_ptr<clone_pair> &p, const bool search_left, const std::shared_ptr<file_index> &file_index) const noexcept
{
	const int x=file_index->at(p->fragment1().file_ptr());
	const int y=file_index->at(p->fragment2().file_ptr());
	
	const auto &grid=this->layer_[grid_2d_coordinate::to_linear(x, y)];
	
	if(search_left)
	{
		// detection_result "left" may have clone pairs which are matched for clone_pair "p"
		return std::count_if(grid.begin(), grid.end(), [&](const auto &mp){ return mp.first==p; });
	}
	// detection_result "right" may have clone pairs which are matched for clone_pair "p"
	return std::count_if(grid.begin(), grid.end(), [&](const auto &mp){ return mp.second==p; });
}

void matching_table::unit::update() noexcept
{
	auto left=this->key_.left()->clone_pair_layer();
	auto right=this->key_.right()->clone_pair_layer();
	this->layer_.resize(left->width());

	for(auto i=left->begin1d(), end=left->end1d(); i!=end; ++i)
	{
		this->layer_[i]=std::move(this->map_mutually((*left)[i], (*right)[i]));
	}
}

bool matching_table::unit::better(const float ok_v, const float good_v, const float ok_max, const float good_max, const float t) noexcept
{
	return (good_v>=t && good_v>=good_max) || (qFuzzyCompare(good_v, good_max) && ok_v>ok_max) || (ok_v>=t && ok_max<t);
}

std::unordered_map<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>> matching_table::unit::map_unidirectionally(const shared_vector<clone_pair> &g1, const shared_vector<clone_pair> &g2) noexcept
{
	std::unordered_map<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>> matched;

	for(const auto &r:g1)
	{
		for(const auto &c:g2)
		{
			auto [ok_max, good_max]=matched.find(r)!=matched.end() ? qMakePair(ok(c, matched[r]), good(c, matched[r])) : qMakePair(threshold_, threshold_);
			auto ok_v=ok(c, r);
			auto good_v=good(c, r);

			if(better(ok_v, good_v, ok_max, good_max, threshold_))
			{
				matched[c]=r;
			}
		}
	}

	return matched;
}

matching_table::unit::value_t matching_table::unit::map_mutually(const shared_vector<clone_pair> &left, const shared_vector<clone_pair> &right) noexcept
{
	auto left_right=map_unidirectionally(left, right);
	auto right_left=map_unidirectionally(right, left);
	
	value_t matched;

	for(const auto &e:left_right)
	{
		matched.push_back(e);
	}

	for(const auto &e:right_left)
	{
		matched.emplace_back(e.second, e.first);
	}

	std::sort(matched.begin(), matched.end());
	matched.erase(std::unique(matched.begin(), matched.end()), matched.end());
	return matched;
}


void matching_table::update() noexcept
{
	for(auto left=this->results_.begin(), left_end=this->results_.end()-1; left!=left_end; ++left)
	{
		for(auto right=left+1, right_end=this->results_.end(); right!=right_end; ++right)
		{
			key key(*left, *right);
			this->values_.emplace(key, unit(key));
		}
	}

	return;
}

void matching_table::append(const std::shared_ptr<detection_result> &result) noexcept
{
	if(this->results_.indexOf(result)>=0)
	{
		return;
	}
	this->results_.append(result);
	std::sort(this->results_.begin(), this->results_.end());
}

void matching_table::append(const shared_list<detection_result> &results) noexcept
{
	for(const auto &r:results)
	{
		if(this->results_.indexOf(r)<0)
		{
			this->results_.append(r);
		}
	}
	std::sort(this->results_.begin(), this->results_.end());
}

void matching_table::remove(const std::shared_ptr<detection_result> &result) noexcept
{
	this->results_.removeOne(result);
	this->update();
}

int matching_table::count_matching_pair(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &p, const std::shared_ptr<file_index> &file_index) const noexcept
{
	int r=0;
	bool search_left;
	for(const auto &u:this->values_)
	{
		search_left=u.first.right()==result;
		if(!search_left && u.first.left()!=result)
		{
			continue;
		}
		r+=u.second.count_matching_pair(p, search_left, file_index);
	}
	return r;
}

bool matching_table::has_matching_pair(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &p, const std::shared_ptr<file_index> &file_index) const noexcept
{
	bool search_left;
	for(const auto &u:this->values_)
	{
		search_left=u.first.right()==result;
		if(!search_left && u.first.left()!=result)
		{
			continue;
		}
		if(u.second.count_matching_pair(p, search_left, file_index)>0)
		{
			return true;
		}
	}
	return false;
}

}

