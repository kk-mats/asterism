#ifndef HEATMAP_LAYER_HPP
#define HEATMAP_LAYER_HPP

#include <optional>
#include <variant>

#include "clone_pair_grid_layer.hpp"
#include "gui/color_selector.hpp"
#include "core/logger.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class clone_size_heatmap_layer final
	: public file_separated_grid_layer<QColor>
{
public:
	clone_size_heatmap_layer(const std::shared_ptr<detection_result> &primitive) noexcept;

	QString name() const noexcept;
	
	QString primitive_name() const noexcept;
	QString primitive_source() const noexcept;

	int min() const noexcept;
	int max() const noexcept;

	bool update(const file_index &file_index) noexcept;

private:
	QString name_;
	std::shared_ptr<detection_result> primitive_;
	int min_, max_;
};


class matching_rate_heatmap_layer final
	: public file_separated_grid_layer<QColor>
{
public:
	matching_rate_heatmap_layer(const std::shared_ptr<detection_result> &primitive1, const std::shared_ptr<detection_result> &primitive2) noexcept;

	QString name() const noexcept;

	QString primitive1_name() const noexcept;
	QString primitive1_source() const noexcept;
	QString primitive2_name() const noexcept;
	QString primitive2_source() const noexcept;

	bool update(const file_index &file_index) noexcept;

private:
	QString name_;
	std::shared_ptr<detection_result> primitive1_, primitive2_;
};

using heatmap_layer=std::variant<clone_size_heatmap_layer, matching_rate_heatmap_layer>;

struct heatmap_layer_name_visitor
{
	QString operator ()(const clone_size_heatmap_layer &h) noexcept;
	QString operator ()(const matching_rate_heatmap_layer &h) noexcept;
};

}


#endif // HEATMAP_LAYER_HPP
