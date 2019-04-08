#include "heatmap_layer.hpp"

namespace asterism
{

heatmap_layer heatmap_layer::colorized_by_clone_pair_size(const clone_pair_grid_layer &source) noexcept
{
	heatmap_layer r(source.width());

	auto max=(*std::max_element(source.begin(), source.end(), [](const auto &g1, const auto &g2){ return g1.size()<g2.size(); })).size();
	auto min=(*std::min_element(source.begin(), source.end(), [](const auto &g1, const auto &g2){ return g1.size()<g2.size(); })).size();

	color_selector selector(Qt::white, 0);
	if(0<min)
	{
		selector.set_anchor(Qt::white, min-1);
	}

	selector.set_anchor(Qt::green, min);
	selector.set_anchor(Qt::red, max);

	for(auto i=r.begin1d(), end=r.end1d(); i!=end; ++i)
	{
		if(auto color=selector.color_at(source[i].size()); !color)
		{
			qCritical()<<heatmap_generating_error::color_index_out_of_range;
			return heatmap_layer();
		}
		else
		{
			r[i]=color.value();
		}
	}

	return r;
}

}
