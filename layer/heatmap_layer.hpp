#ifndef HEATMAP_LAYER_HPP
#define HEATMAP_LAYER_HPP

#include "file_separated_grid_layer.hpp"
#include "clone_pair_grid_layer.hpp"
#include "gui/color_selector.hpp"
#include "core/logger.hpp"

namespace asterism
{


class heatmap_layer
		: public file_separated_grid_layer<QColor>
{
public:
	using file_separated_grid_layer::file_separated_grid_layer;

	static heatmap_layer colorized_by_clone_pair_size(const clone_pair_grid_layer &source) noexcept;
};

}


#endif // HEATMAP_LAYER_HPP
