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

	static std::optional<heatmap_layer> colorized_by_clone_pair_size(const std::shared_ptr<clone_pair_grid_layer> &clone_pair_layer, const std::shared_ptr<file_index> &file_index) noexcept;

private:
	std::shared_ptr<clone_pair_grid_layer> clone_pair_layer_;
};

}


#endif // HEATMAP_LAYER_HPP
