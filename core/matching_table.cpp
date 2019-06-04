#include "matching_table.hpp"

namespace asterism
{

query::query(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &body) noexcept
	: result_(result), body_(body)
{}

std::shared_ptr<detection_result> query::result() const noexcept
{
	return this->result_;
}

std::shared_ptr<clone_pair> query::body() const noexcept
{
	return this->body_;
}

bool query::operator==(const query & other) const noexcept
{
	return this->result_==other.result_ && this->body_==other.body_;
}

response::response(const std::shared_ptr<detection_result> &result, const shared_vector<clone_pair> &clone_pairs) noexcept
	: result_(result), clone_pairs_(clone_pairs)
{}

std::shared_ptr<detection_result> response::result() const noexcept
{
	return this->result_;
}

int response::size() const noexcept
{
	return this->clone_pairs_.size();
}

shared_vector<clone_pair>::const_iterator response::begin() const noexcept
{
	return this->clone_pairs_.begin();
}

shared_vector<clone_pair>::const_iterator response::end() const noexcept
{
	return this->clone_pairs_.end();
}

std::shared_ptr<clone_pair> response::operator [](const int i) const noexcept
{
	return this->clone_pairs_[i];
}


matching_table::key::key(const key &k) noexcept
	: r_(k.r_)
{}

matching_table::key::key(key &&k) noexcept
	: r_(std::move(k.r_))
{}

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

matching_table::key& matching_table::key::operator =(const key &other) noexcept
{
	if(this==&other)
	{
		this->r_=other.r_;
	}
	return *this;
}

matching_table::key& matching_table::key::operator =(key &&other) noexcept
{
	if(this==&other)
	{
		this->r_=std::move(other.r_);
	}
	return *this;
}

bool matching_table::key::operator==(const key &other) const noexcept
{
	return this->r_==other.r_;
}

matching_table::unit::unit(const unit &u) noexcept
	: key_(u.key_), layer_(u.layer_)
{}

matching_table::unit::unit(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept
	: key_(left, right)
{
	this->update();
}

matching_table::unit& matching_table::unit::operator=(const unit & other) noexcept
{
	if(this!=&other)
	{
		this->key_=other.key_;
		this->layer_=other.layer_;
	}

	return *this;
}

matching_table::unit& matching_table::unit::operator=(unit &&other) noexcept
{
	if(this!=&other)
	{
		this->key_=std::move(other.key_);
		this->layer_=std::move(other.layer_);
	}

	return *this;
}

shared_vector<clone_pair> matching_table::unit::matched_pair(const std::shared_ptr<clone_pair> &p, const bool search_left) const noexcept
{
	const int x=p->fragment1().file_ptr()->id();
	const int y=p->fragment2().file_ptr()->id();
	
	const auto &grid=this->layer_[grid_2d_coordinate::to_linear(x, y)];
	shared_vector<clone_pair> r;

	if(search_left)
	{
		// detection_result "left" may have clone pairs which are matched for clone_pair "p"
		for(const auto &mp:grid)
		{
			if(mp.first==p)
			{
				r.push_back(mp.second);
			}
		}
	}
	else
	{
		// detection_result "right" may have clone pairs which are matched for clone_pair "p"
		for(const auto &mp:grid)
		{
			if(mp.second==p)
			{
				r.push_back(mp.first);
			}
		}
	}
	return r;
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

shared_vector<clone_pair> matching_table::unit::matched_in_left() const noexcept
{
	shared_vector<clone_pair> r;
	for(const auto &g:this->layer_)
	{
		for(const auto &mp:g)
		{
			r.push_back(mp.first);
		}
	}
	return r;
}

shared_vector<clone_pair> matching_table::unit::matched_in_right() const noexcept
{
	shared_vector<clone_pair> r;
	for(const auto &g:this->layer_)
	{
		for(const auto &mp:g)
		{
			r.push_back(mp.second);
		}
	}
	return r;
}

matching_table::key matching_table::unit::unit_key() const noexcept
{
	return this->key_;
}

bool matching_table::unit::better(const float ok_v, const float good_v, const float ok_max, const float good_max, const float t) noexcept
{
	return ok_v>=t && ok_v>ok_max;
	//return (good_v>=t && good_v>=good_max) || (qFuzzyCompare(good_v, good_max) && ok_v>ok_max) || (ok_v>=t && ok_max<t);
}


std::unordered_map<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>> matching_table::unit::map_unidirectionally(const shared_vector<clone_pair> &g1, const shared_vector<clone_pair> &g2) noexcept
{
	std::unordered_map<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>> matched;

	
	for(const auto &r:g1)
	{
		for(const auto &c:g2)
		{
			/*
			if(covers(c->fragment1(), r->fragment1(), threshold_) && covers(c->fragment2(), r->fragment2(), threshold_))
			{
				matched[c]=r;
			}
			*/
			
			auto ok_max=matched.find(r)!=matched.end() ? ok(c, matched[r]) : threshold_;
			auto ok_v=ok(c, r);

			if(ok_v>=ok_max)
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
	for(auto left=0; left<this->results_.size()-1; ++left)
	{
		for(auto right=left+1; right<this->results_.size(); ++right)
		{
			unit u(this->results_[left], this->results_[right]);
			auto k=u.unit_key();
			this->values_.emplace_back(k, u);
		}
	}
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

void matching_table::append(const shared_vector<detection_result> &results) noexcept
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
	this->values_.erase(std::remove_if(this->values_.begin(), this->values_.end(), [&](const auto &p){ return p.first.left()==result || p.first.right()==result; }), this->values_.end());
}

std::vector<response> matching_table::matched_pair(const query &q) const noexcept
{
	bool search_left;
	std::vector<response> r;

	for(const auto &u:this->values_)
	{
		search_left=u.first.right()==q.result();
		if(!search_left && u.first.left()!=q.result())
		{
			continue;
		}
		r.emplace_back(search_left ? u.first.left() : u.first.right(), u.second.matched_pair(q.body(), search_left));
	}
	return r;
}

bool matching_table::has_matching_pair(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &p) const noexcept
{
	bool search_left;
	for(const auto &u:this->values_)
	{
		search_left=u.first.right()==result;
		if(!search_left && u.first.left()!=result)
		{
			continue;
		}
		if(u.second.matched_pair(p, search_left).size()>0)
		{
			return true;
		}
	}
	return false;
}

bool matching_table::has_matching_pair_restrict(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &p) const noexcept
{
	bool search_left;
	int matched=1;
	for(const auto &u:this->values_)
	{
		search_left=u.first.right()==result;
		if(!search_left && u.first.left()!=result)
		{
			continue;
		}
		if(u.second.matched_pair(p, search_left).size()>0)
		{
			++matched;
		}
	}
	return matched==this->results_.size();
}


uint qHash(const query &key, uint seed) noexcept
{
	return qHash(key.body_, seed);
}

}

