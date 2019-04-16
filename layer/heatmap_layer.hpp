#ifndef HEATMAP_LAYER_HPP
#define HEATMAP_LAYER_HPP

#include <optional>

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
	enum class colorized_mathod
	{
		matching_rate,
		clone_pair_size
	};

	static std::optional<heatmap_layer> colorized_by_clone_pair_size(const std::shared_ptr<clone_pair_grid_layer> &clone_pair_layer, const std::shared_ptr<file_index> &file_index_ptr) noexcept;

	void update(const std::shared_ptr<file_index> &file_index_ptr) noexcept;

private:
	colorized_mathod method_;
	std::shared_ptr<clone_pair_grid_layer> clone_pair_layer_;

	bool make_layer() noexcept;
};

}


#endif // HEATMAP_LAYER_HPP
