#ifndef CLONE_SET_HPP
#define CLONE_SET_HPP

#include <vector>
#include <functional>

#include <QSet>
#include <BronKerbosch/bron-kerbosch_utils.h>

#include "clone_pair.hpp"

namespace asterism
{

using clone_set=QSet<fragment>;

void edge(BronKerbosch::Graph<fragment> &G, const std::shared_ptr<clone_pair> &p)
{
	auto itr1=std::find_if(G.begin(), G.end(), [&](const auto &v) { return v.id==p->fragment1(); });
	if(itr1==G.end())
	{
		G.push_front(p->fragment1());
		itr1=G.begin();
	}

	auto itr2=std::find_if(G.begin(), G.end(), [&](const auto &v) { return v.id==p->fragment2(); });
	if(itr2==G.end())
	{
		G.push_front(p->fragment2());
		itr2=G.begin();
	}

	itr1->ns.insert(p->fragment2());
	itr2->ns.insert(p->fragment1());
}

void aggregator(std::forward_list<BronKerbosch::Graph<fragment>> &all, BronKerbosch::Graph<fragment> R, BronKerbosch::Graph<fragment> P, BronKerbosch::Graph<fragment>)
{
	all.push_front(R);
	for(const auto &v:R)
	{
		P.remove(v);
	}

	if(!P.empty())
	{
		BronKerbosch::solve<fragment>({{}}, P, {{}}, std::bind(aggregator, std::ref(all), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}
}


std::vector<clone_set> to_clone_set(const shared_set<clone_pair> &clone_pairs)
{
	BronKerbosch::Graph<fragment> G;
	for(const auto &p:clone_pairs)
	{
		edge(G, p);
	}

	std::forward_list<BronKerbosch::Graph<fragment>> all;
	aggregator(all, {{}}, G, {{}});

	std::vector<clone_set> all_set;

	for(const auto &s:all)
	{
		if(s.empty())
		{
			continue;
		}

		clone_set set;
		for(const auto &v:s)
		{
			set.insert(v.id);
		}

		all_set.push_back(std::move(set));
	}

	return all_set;
}

}

#endif // CLONE_SET_HPP