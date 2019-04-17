#include "heatmap_layer.hpp"

namespace asterism
{

std::optional<heatmap_layer> heatmap_layer::colorized_by_clone_pair_size(const std::shared_ptr<clone_pair_grid_layer> &clone_pair_layer, const file_index &file_index) noexcept
{
	heatmap_layer r(file_index);
	r.method_=colorized_mathod::clone_pair_size;
	r.clone_pair_layer_=clone_pair_layer;

	return r.make_layer() ? std::make_optional(r) : std::nullopt;
}

void heatmap_layer::update(const file_index &file_index) noexcept
{
	this->resize(file_index);
	this->make_layer();
}

bool heatmap_layer::make_layer() noexcept
{
	switch(this->method_)
	{
		case heatmap_layer::colorized_mathod::clone_pair_size:
		{
			auto max=(*std::max_element(this->clone_pair_layer_->begin(), this->clone_pair_layer_->end(), [](const auto &g1, const auto &g2){ return g1.size()<g2.size(); })).size();
			auto min=(*std::min_element(this->clone_pair_layer_->begin(), this->clone_pair_layer_->end(), [](const auto &g1, const auto &g2){ return g1.size()<g2.size(); })).size();

			color_selector selector(Qt::white, 0);
			if(0<min)
			{
				selector.set_anchor(Qt::white, min-1);
			}

			selector.set_anchor(Qt::green, min);
			selector.set_anchor(Qt::red, max);

			for(auto i=this->begin1d(), end=this->end1d(); i!=end; ++i)
			{
				if(auto color=selector.color_at((*this->clone_pair_layer_)[i].size()); !color)
				{
					qCritical()<<heatmap_generating_error::color_index_out_of_range;
					return false;
				}
				else
				{
					(*this)[i]=color.value();
				}
			}
		}
	}

	return true;
}

}
