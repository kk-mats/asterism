#include "bk.hpp"

namespace asterism
{

shared_set<clone_pair> bk_fuser::run(const shared_list<detection_result>& results, const matching_table & m) noexcept
{
	shared_set<clone_pair> f;
	for(auto i=(*results.begin())->clone_pair_layer()->begin1d(), end=(*results.begin())->clone_pair_layer()->end1d(); i!=end; ++i)
	{
		QSet<query> p;
		for(const auto &r:results)
		{
			for(const auto &cp:(*r->clone_pair_layer())[i])
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
				f.insert(maximal(r));
			}
		}
	}

	return f;
}

bool bk_fuser::bron_kerbosch(shared_set<clone_pair> &r, QSet<query>& p, const QSet<query>& x, const matching_table & m) noexcept
{
	if(p.size()==0 && x.size()==0)
	{
		return true;
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
		if(bron_kerbosch(r, pp.intersect(neighbor), xx.intersect(neighbor), m))
		{
			return true;
		}
		xx.insert(*v);
	}

	return false;
}

std::shared_ptr<clone_pair> bk_fuser::maximal(const shared_set<clone_pair> &p) noexcept
{
	QVector<fragment> f1, f2;

	for(const auto &pp:p)
	{
		f1.append(pp->fragment1());
		f2.append(pp->fragment2());
	}

	return std::make_shared<clone_pair>(maximal(f1), maximal(f2), -1);
}

fragment bk_fuser::maximal(const QVector<fragment> &fragments) noexcept
{
	QVector<fragment> ff=fragments;
	const auto file_ptr=ff[0].file_ptr();
	bool changed=false;
	
	do
	{
		changed=false;
		for(int i=0; i<ff.size()-1; ++i)
		{
			for(int j=i; j<ff.size(); ++j)
			{
				if(ff[i].is_overlapped(ff[j]))
				{
					fragment f(file_ptr, std::min(ff[i].begin(), ff[j].begin()), std::max(ff[i].end(), ff[j].end()));
					ff.removeAt(i);
					ff.remove(i<j ? j-1 : j);
					ff.append(f);
					changed=true;
				}
			}
		}
	}
	while(changed);

	return *std::max(ff.begin(), ff.end(), [](const auto &f1, const auto &f2){ return f1->end()-f1->begin()<f2->end()-f2->begin(); });
}

}