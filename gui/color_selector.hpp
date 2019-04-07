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
	color_selector(const QColor &color, const uint32_t index=0) noexcept;

	void set_anchor(const QColor &color, const uint32_t index) noexcept;

	std::optional<QColor> color_at(const uint32_t index) noexcept;

private:
	uint32_t index_begin_, index_end_;
	QMap<uint32_t, QColor> color_source_;
};

}


#endif // COLOR_SELECTOR_HPP
