#ifndef COLOR_SELECTOR_HPP
#define COLOR_SELECTOR_HPP

#include <QColor>
#include <QMap>

#include <optional>
#include <vector>

namespace asterism
{
struct signed_color
{
	signed_color() noexcept;
	signed_color(const QColor &c) noexcept;
	signed_color(const int r, const int g, const int b) noexcept;

	operator QColor() const noexcept;

	int r, g, b;
};

signed_color operator +(const signed_color &c1, const signed_color &c2) noexcept;
signed_color operator -(const signed_color &c1, const signed_color &c2) noexcept;
signed_color operator *(const signed_color &c, const float f) noexcept;
signed_color operator /(const signed_color &c, const float f) noexcept;


class color_selector
{
public:
	color_selector() noexcept=default;
	color_selector(const int index, const QColor &color) noexcept;
	color_selector(const std::vector<std::pair<int, QColor>> &anchors) noexcept;

	void set_anchor(const int index, const QColor &color) noexcept;

	std::optional<QColor> color_at(const int index) noexcept;

	int first() const noexcept;
	int last() const noexcept;

	QMap<int, signed_color>::const_key_value_iterator begin() const noexcept;
	QMap<int, signed_color>::const_key_value_iterator end() const noexcept;

private:
	int first_=std::numeric_limits<int>::max(), last_;
	QMap<int, signed_color> color_source_;
};

}


#endif // COLOR_SELECTOR_HPP
