#ifndef BK_HPP
#define BK_HPP

#include "matching_table.hpp"

namespace asterism
{

shared_set<clone_pair> bron_kerbosch(shared_set<clone_pair> &r, QSet<query> &p, const QSet<query> &x, const matching_table &m) noexcept
{
	if(p.size()==0 && x.size()==0)
	{
		return r;
	}

	auto pp=p;
	auto xx=x;
	for(auto v=pp.begin(); v!=pp.end(); v=pp.erase(v))
	{
		r.insert(v->body());
		QSet<query> neighbor;
		for(const auto &n:m.matched_pair(*v))
		{
			for(const auto &mp:n)
			{
				neighbor.insert(query(n.result(), mp));
			}
		}
		bron_kerbosch(r, pp.intersect(neighbor), xx.intersect(neighbor), m);
		xx.insert(*v);
	}
}


shared_set<clone_pair> fuse(const shared_list<detection_result> &results, const matching_table &m)
{
	shared_set<clone_pair> f;
	QSet<query> p;

	for(const auto &r:results)
	{
		for(const auto &cp:r->clone_pairs())
		{
			p.insert(query(r, cp));
		}
	}

	while(!p.isEmpty())
	{
		shared_set<clone_pair> r;
		bron_kerbosch(r, p, QSet<query>(), m);
		if(r.size()>=2)
		{
			f.insert(maximal_clone_pair(r));
		}
	}

	return f;
}

std::shared_ptr<clone_pair> maximal_clone_pair(const shared_set<clone_pair> &p) noexcept
{
	std::shared_ptr<clone_pair> r=*p.begin();
	for(auto i=p.begin()+1, end=p.end(); i!=end; ++i)
	{
		if(!r->fragment1().length()>=(*i)->fragment1().length() || !r->fragment2().length()>=(*i)->fragment2().length())
		{
			r=*i;
		}
	}
	return r;
}

}

#endif // BK_HPP
