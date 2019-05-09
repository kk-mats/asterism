#ifndef HEATMAP_LAYER_HPP
#define HEATMAP_LAYER_HPP

#include <optional>
#include <variant>

#include "clone_pair_grid_layer.hpp"
#include "gui/color_selector.hpp"
#include "core/matching_table.hpp"
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
		color_selector selector() const noexcept;
		std::vector<std::pair<QString, QString>> details() const noexcept;

		bool update(const std::shared_ptr<detection_result> &primitive) noexcept;

	private:
		int min_=std::numeric_limits<int>::max();
		int max_=0;
		int sum_=0;
		color_selector selector_=color_selector(Qt::white, 0);
		void make(const std::shared_ptr<detection_result> &primitive) noexcept;
	};


	class matching_rate final
		: public file_separated_grid_layer<QColor>
	{
	public:
		static void bind(const std::shared_ptr<file_index> &file_index, const std::shared_ptr<matching_table> &matching_table) noexcept;
		matching_rate() noexcept=default;
		matching_rate(const std::shared_ptr<detection_result> &primitive) noexcept;

		int average_matching_rate() const noexcept;
		color_selector selector() const noexcept;
		std::vector<std::pair<QString, QString>> details() const noexcept;

		bool update(const std::shared_ptr<detection_result> &primitive) noexcept;

	private:
		static inline std::shared_ptr<file_index> file_index_=nullptr;
		static inline std::shared_ptr<matching_table> matching_table_=nullptr;
		static inline color_selector selector_=color_selector(
			{
				{0, QColor(233, 30, 30)},
				{99, QColor(204, 255, 144)},
				{100, Qt::darkBlue}
			}
		);
		int average_matching_rate_=0;
	};


	struct method final
	{
		method() noexcept=default;
		struct clone_pair_size final{};
		struct matching_rate final{};
	};

	heatmap_layer() noexcept=default;
	heatmap_layer(const std::shared_ptr<detection_result> &primitive, const method::clone_pair_size) noexcept;
	heatmap_layer(const std::shared_ptr<detection_result> &primitive, const method::matching_rate) noexcept;
	
	template <class T>
	using is_convertible_from=typename std::enable_if_t<std::is_same_v<T, clone_pair_size> || std::is_same_v<T, matching_rate>>;

	void change_method(const method::clone_pair_size) noexcept;
	void change_method(const method::matching_rate) noexcept;

	bool update() noexcept;

	int method_index() const noexcept;
	QString name() const noexcept;
	int width() const noexcept;
	color_selector selector() const noexcept;
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
