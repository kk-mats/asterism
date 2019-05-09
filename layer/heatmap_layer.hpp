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


class heatmap_layer final
{
public:
	class clone_pair_size final
		: public file_separated_grid_layer<QColor>
	{
	public:
		clone_pair_size() noexcept=default;
		clone_pair_size(const std::shared_ptr<detection_result> &primitive) noexcept;

		int min() const noexcept;
		int max() const noexcept;

		std::vector<std::pair<QString, QString>> details() const noexcept;

		bool update(const std::shared_ptr<detection_result> &primitive) noexcept;

	private:
		int min_=std::numeric_limits<int>::max();
		int max_=0;
		int sum_=0;

		void make(const std::shared_ptr<detection_result> &primitive) noexcept;
	};


	class matching_rate final
		: public file_separated_grid_layer<QColor>
	{
	public:
		matching_rate() noexcept=default;
		matching_rate(const std::shared_ptr<detection_result> &primitive) noexcept;

		int average_matching_rate() const noexcept;

		std::vector<std::pair<QString, QString>> details() const noexcept;

		bool update(const std::shared_ptr<detection_result> &primitive) noexcept;

	private:
		int average_matching_rate_=0;
	};


	struct rule final
	{
		rule() noexcept=default;
		struct clone_pair_size final{};
		struct matching_rate final{};
	};

	heatmap_layer() noexcept=default;
	heatmap_layer(const std::shared_ptr<detection_result> &primitive, const rule::clone_pair_size) noexcept;
	heatmap_layer(const std::shared_ptr<detection_result> &primitive, const rule::matching_rate) noexcept;
	
	template <class T>
	using is_convertible_from=typename std::enable_if_t<std::is_same_v<T, clone_pair_size> || std::is_same_v<T, matching_rate>>;

	void change_rule(const rule::clone_pair_size) noexcept;
	void change_rule(const rule::matching_rate) noexcept;

	bool update() noexcept;

	int rule_index() const noexcept;
	QString name() const noexcept;
	int width() const noexcept;
	std::vector<std::pair<QString, QString>> details() const noexcept;

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
	std::shared_ptr<detection_result> primitive_;
	std::variant<clone_pair_size, matching_rate> value_;
};

}


#endif // HEATMAP_LAYER_HPP
