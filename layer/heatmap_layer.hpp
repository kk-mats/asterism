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
	clone_size_heatmap_layer() noexcept=default;
	clone_size_heatmap_layer(const std::shared_ptr<detection_result> &primitive) noexcept;

	QString name() const noexcept;
	
	QString primitive_name() const noexcept;
	QString primitive_source() const noexcept;

	int min() const noexcept;
	int max() const noexcept;

	bool update() noexcept;

private:
	QString name_;
	std::shared_ptr<detection_result> primitive_;
	int min_, max_;
};


class matching_rate_heatmap_layer final
	: public file_separated_grid_layer<QColor>
{
public:
	matching_rate_heatmap_layer() noexcept=default;
	matching_rate_heatmap_layer(const std::shared_ptr<detection_result> &primitive1, const std::shared_ptr<detection_result> &primitive2) noexcept;

	QString name() const noexcept;

	QString primitive1_name() const noexcept;
	QString primitive1_source() const noexcept;
	QString primitive2_name() const noexcept;
	QString primitive2_source() const noexcept;

	bool update() noexcept;

private:
	QString name_;
	std::shared_ptr<detection_result> primitive1_, primitive2_;
};


class heatmap_layer
{
public:
	heatmap_layer() noexcept=default;
	heatmap_layer(const std::shared_ptr<detection_result> &primitive) noexcept;
	heatmap_layer(const std::shared_ptr<detection_result> &primitive1, const std::shared_ptr<detection_result> &primitive2) noexcept;

	template <class T>
	using is_convertible_from=typename std::enable_if_t<std::is_same_v<T, clone_size_heatmap_layer> || std::is_same_v<T, matching_rate_heatmap_layer>>;

	bool update() noexcept;

	QString name() const noexcept;
	int width() const noexcept;

	const QColor& operator [](const grid_coordinate &coordinate) const noexcept;
	const QColor& operator [](const int i) const noexcept;

	template <class T, is_convertible_from<T> =nullptr>
	heatmap_layer& operator =(const T &layer)
	{
		this->value_=layer;
		return *this;
	}

	template <class T, is_convertible_from<T> =nullptr>
	heatmap_layer& operator =(T &&layer)
	{
		this->value_=std::move(layer);
		return *this;
	}

private:
	std::variant<clone_size_heatmap_layer, matching_rate_heatmap_layer> value_;
};

}


#endif // HEATMAP_LAYER_HPP
