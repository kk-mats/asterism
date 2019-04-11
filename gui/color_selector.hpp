#ifndef COLOR_SELECTOR_HPP
#define COLOR_SELECTOR_HPP

#include <QColor>
#include <QMap>
#include <optional>

namespace asterism
{


QColor operator +(const QColor &c1, const QColor &c2) noexcept;
QColor operator -(const QColor &c1, const QColor &c2) noexcept;
QColor operator *(const QColor &c, const float &f) noexcept;
QColor operator /(const QColor &c, const float &f) noexcept;

class color_selector
{
public:
	color_selector(const QColor &color, const int index=0) noexcept;

	void set_anchor(const QColor &color, const int index) noexcept;

	std::optional<QColor> color_at(const int index) noexcept;

private:
	int index_begin_, index_end_;
	QMap<int, QColor> color_source_;
};

}


#endif // COLOR_SELECTOR_HPP
