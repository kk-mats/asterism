#include "heatmap_layer.hpp"

namespace asterism
{

bool heatmap_layer::colorized_by_clone_pair_size(const shared_set<clone_pair> &clone_pairs) noexcept
{
	auto max=(*std::max_element(source.begin(), source.end(), [](const auto &g1, const auto &g2){ return g1.size()<g2.size(); })).size();
	auto min=(*std::min_element(source.begin(), source.end(), [](const auto &g1, const auto &g2){ return g1.size()<g2.size(); })).size();

	color_selector selector(Qt::white, 0);
	if(0<min)
	{
		selector.set_anchor(Qt::white, min-1);
	}

	selector.set_anchor(Qt::green, min);
	selector.set_anchor(Qt::red, max);

	for(auto i=this->begin1d(), end=this->end1d(); i!=end; ++i)
	{
		if(auto color=selector.color_at(source[i].size()); !color)
		{
			qCritical()<<heatmap_generating_error::color_index_out_of_range;
			return false;
		}
		else
		{
			(*this)[i]=color.value();
		}
	}

	return r;
}

}
