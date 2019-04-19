#include "color_selector.hpp"

namespace asterism
{

signed_color::signed_color() noexcept
	: r(0), g(0), b(0)
{}

signed_color::signed_color(const QColor &c) noexcept
	: r(c.red()), g(c.green()), b(c.blue())
{}

signed_color::signed_color(const int r, const int g, const int b) noexcept
	: r(r), g(g), b(b)
{}

signed_color::operator QColor() const noexcept
{
	return QColor(
		std::clamp(this->r, 0, 255),
		std::clamp(this->g, 0, 255),
		std::clamp(this->b, 0, 255)
	);

}

signed_color operator +(const signed_color &c1, const signed_color &c2) noexcept
{
	return signed_color(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);
}

signed_color operator -(const signed_color &c1, const signed_color &c2) noexcept
{
	return signed_color(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b);
}

signed_color operator *(const signed_color &c, const float f) noexcept
{
	return signed_color(c.r*f, c.g*f, c.b*f);
}

signed_color operator /(const signed_color &c, const float f) noexcept
{
	return signed_color(c.r/f, c.g/f, c.b/f);
}

color_selector::color_selector(const QColor &color, const int index) noexcept
	: index_begin_(index), index_end_(index)
{
	this->color_source_[index]=signed_color(color);
}


void color_selector::set_anchor(const QColor &color, const int index) noexcept
{
	if(index<this->index_begin_)
	{
		this->index_begin_=index;
	}
	else if(this->index_end_<index)
	{
		this->index_end_=index;
	}

	this->color_source_[index]=signed_color(color);
}

std::optional<QColor> color_selector::color_at(const int index) noexcept
{
	if(index<this->index_begin_ || this->index_end_<index)
	{
		return std::nullopt;
	}

	auto keys=this->color_source_.keys();
	for(int i=0; i<keys.size()-1; ++i)
	{
		if(keys[i]<=index && index<=keys[i+1])
		{
			const auto base=this->color_source_[keys[i]], next=this->color_source_[keys[i+1]];
			const auto d=(index-keys[i])/float(keys[i+1]-keys[i]);
			return QColor(base+(next-base)*d);
		}
	}

	return std::nullopt;
}

}
