#include "heatmap_layer.hpp"

namespace asterism
{

std::optional<heatmap_layer> heatmap_layer::colorized_by_clone_pair_size(const std::shared_ptr<clone_pair_grid_layer> &clone_pair_layer, const std::shared_ptr<file_index> &file_index_ptr) noexcept
{
	heatmap_layer r(file_index_ptr);
	r.clone_pair_layer_=clone_pair_layer;

	auto max=(*std::max_element(r.clone_pair_layer_->begin(), r.clone_pair_layer_->end(), [](const auto &g1, const auto &g2){ return g1.size()<g2.size(); })).size();
	auto min=(*std::min_element(r.clone_pair_layer_->begin(), r.clone_pair_layer_->end(), [](const auto &g1, const auto &g2){ return g1.size()<g2.size(); })).size();

	color_selector selector(Qt::white, 0);
	if(0<min)
	{
		selector.set_anchor(Qt::white, min-1);
	}

	selector.set_anchor(Qt::green, min);
	selector.set_anchor(Qt::red, max);

	for(auto i=r.begin1d(), end=r.end1d(); i!=end; ++i)
	{
		if(auto color=selector.color_at((*r.clone_pair_layer_)[i].size()); !color)
		{
			qCritical()<<heatmap_generating_error::color_index_out_of_range;
			return std::nullopt;
		}
		else
		{
			r[i]=color.value();
		}
	}

	return r;
}

}
