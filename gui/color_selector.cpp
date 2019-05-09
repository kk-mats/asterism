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
	: first_(index), last_(index)
{
	this->color_source_[index]=signed_color(color);
}

color_selector::color_selector(const std::vector<std::pair<int, QColor>> &anchors) noexcept
{
	for(const auto &a:anchors)
	{
		this->set_anchor(a.first, a.second);
	}
}


void color_selector::set_anchor(const int index, const QColor &color) noexcept
{
	if(index<this->first_)
	{
		this->first_=index;
	}
	else if(this->last_<index)
	{
		this->last_=index;
	}

	this->color_source_[index]=signed_color(color);
}

std::optional<QColor> color_selector::color_at(const int index) noexcept
{
	if(index<this->first_ || this->last_<index)
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

int color_selector::first() const noexcept
{
	return this->first_;
}

int color_selector::last() const noexcept
{
	return this->last_;
}

QMap<int, signed_color>::const_key_value_iterator color_selector::begin() const noexcept
{
	return this->color_source_.constKeyValueBegin();
}

QMap<int, signed_color>::const_key_value_iterator color_selector::end() const noexcept
{
	return this->color_source_.constKeyValueEnd();
}

}
