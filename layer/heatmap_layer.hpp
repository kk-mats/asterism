#ifndef HEATMAP_LAYER_HPP
#define HEATMAP_LAYER_HPP

#include "file_separated_grid_layer.hpp"
#include "clone_pair_grid_layer.hpp"
#include "gui/color_selector.hpp"
#include "core/logger.hpp"
#include "model/detection_result.hpp"

namespace asterism
{


class heatmap_layer
		: public file_separated_grid_layer<QColor>
{
public:
	using file_separated_grid_layer::file_separated_grid_layer;

	bool colorized_by_clone_pair_size(const shared_set<clone_pair> &clone_pairs) noexcept;

private:
	std::weak_ptr<clone_pair_grid_layer> clone_pair_layer_;
};

}


#endif // HEATMAP_LAYER_HPP
