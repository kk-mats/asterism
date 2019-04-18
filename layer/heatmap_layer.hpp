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

	using file_separated_grid_layer::file_separated_grid_layer;

	static std::optional<heatmap_layer> colorized_by_clone_pair_size(const std::shared_ptr<clone_pair_grid_layer> &clone_pair_layer, const file_index &file_index) noexcept;

	bool update(const file_index &file_index) noexcept;

private:
	static inline const QColor white=QColor(255, 255, 255);
	static inline const QColor green=QColor(76, 175, 80);
	static inline const QColor red=QColor(244, 67, 54);

	colorized_mathod method_;
	std::shared_ptr<clone_pair_grid_layer> clone_pair_layer_;

	bool make_layer() noexcept;
};

}


#endif // HEATMAP_LAYER_HPP
