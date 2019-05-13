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
		color_selector selector_=color_selector(0, Qt::white);
		void make(const std::shared_ptr<detection_result> &primitive) noexcept;
	};


	class mismatch_rate final
		: public file_separated_grid_layer<QColor>
	{
	public:
		static void bind( const std::shared_ptr<matching_table> &matching_table) noexcept;
		mismatch_rate() noexcept=default;
		mismatch_rate(const std::shared_ptr<detection_result> &primitive) noexcept;

		color_selector selector() const noexcept;
		std::vector<std::pair<QString, QString>> details() const noexcept;

		bool update(const std::shared_ptr<detection_result> &primitive) noexcept;

	private:
		static inline std::shared_ptr<matching_table> matching_table_=nullptr;
		static inline color_selector selector_=color_selector(
			{
				{1, QColor(0xf5, 0xfc, 0x94)}, // light yellow
				{50, QColor(0xff, 0xb2, 0x00)}, // yellow
				{100, QColor(0xff, 0x00, 0x00)}  // red
			}
		);
		int average_mismatch_rate_=0;
	};


	struct method final
	{
		method() noexcept=default;
		struct clone_pair_size final{};
		struct mismatch_rate final{};
	};

	heatmap_layer() noexcept=default;
	heatmap_layer(const std::shared_ptr<detection_result> &primitive, const method::clone_pair_size) noexcept;
	heatmap_layer(const std::shared_ptr<detection_result> &primitive, const method::mismatch_rate) noexcept;
	
	template <class T>
	using is_convertible_from=typename std::enable_if_t<std::is_same_v<T, clone_pair_size> || std::is_same_v<T, mismatch_rate>>;

	void change_method(const method::clone_pair_size) noexcept;
	void change_method(const method::mismatch_rate) noexcept;

	bool update() noexcept;

	int method_index() const noexcept;
	QString name() const noexcept;
	std::shared_ptr<detection_result> primitive() const noexcept;
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
	std::variant<clone_pair_size, mismatch_rate> value_;
};

}


#endif // HEATMAP_LAYER_HPP
