#include "clone_class.hpp"

namespace asterism
{

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

std::vector<clone_class> to_clone_class(const shared_set<clone_pair> &clone_pairs)
{
	BronKerbosch::Graph<fragment> G;
	for(const auto &p:clone_pairs)
	{
		edge(G, p);
	}

	std::forward_list<BronKerbosch::Graph<fragment>> all;
	aggregator(all, {{}}, G, {{}});

	std::vector<clone_class> all_set;

	for(const auto &s:all)
	{
		if(s.empty())
		{
			continue;
		}

		clone_class set;
		for(const auto &v:s)
		{
			set.insert(v.id);
		}

		all_set.push_back(std::move(set));
	}

	return all_set;
}

}