#ifndef COLOR_SELECTOR_HPP
#define COLOR_SELECTOR_HPP

#include <QColor>
#include <QMap>
#include <optional>

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
	color_selector(const QColor &color, const int index=0) noexcept;

	void set_anchor(const QColor &color, const int index) noexcept;

	std::optional<QColor> color_at(const int index) noexcept;

private:
	int index_begin_, index_end_;
	QMap<int, signed_color> color_source_;
};

}


#endif // COLOR_SELECTOR_HPP
