#include "color_selector.hpp"

namespace asterism
{

QColor operator +(const QColor &c1, const QColor &c2) noexcept
{
	return QColor(c1.red()+c2.red(), c1.green()+c2.green(), c1.blue()+c2.blue());
}

QColor operator -(const QColor &c1, const QColor &c2) noexcept
{
	return QColor(c1.red()-c2.red(), c1.green()-c2.green(), c1.blue()-c2.blue());
}

QColor operator *(const QColor &c, const float &f) noexcept
{
	return QColor(c.red()*f, c.green()*f, c.blue()*f);
}

QColor operator /(const QColor &c, const float &f) noexcept
{
	return QColor(c.red()/f, c.green()/f, c.blue()/f);
}

color_selector::color_selector(const QColor &color, const uint32_t index) noexcept
	: index_begin_(index), index_end_(index)
{
	this->color_source_[index]=color;
}


void color_selector::set_anchor(const QColor &color, const uint32_t index) noexcept
{
	if(index<this->index_begin_)
	{
		this->index_begin_=index;
	}
	else if(this->index_end_<index)
	{
		this->index_end_=index;
	}

	this->color_source_[index]=color;
}

std::optional<QColor> color_selector::color_at(const uint32_t index) noexcept
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
			return this->color_source_[i]+(this->color_source_[i+1]-this->color_source_[i])/(keys[i+1]-keys[i])*index;
		}
	}

	return std::nullopt;
}

}
