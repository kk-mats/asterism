#include "file_separated_grid_layer.hpp"

namespace asterism
{

grid_2d_coordinate::grid_2d_coordinate(const file::id_t &x, const file::id_t &y) noexcept
	: x_y_(this->canonical(x, y))
{}

grid_2d_coordinate::grid_2d_coordinate(file::id_t &&x, file::id_t &&y) noexcept
	: x_y_(this->canonical(std::move(x), std::move(y)))
{}

uint32_t grid_2d_coordinate::to_linear() const noexcept
{
	return this->x_y_.first.id()+this->x_y_.second.id()*(this->x_y_.second.id()+1)/2;
}

file::id_t grid_2d_coordinate::x() const noexcept
{
	return this->x_y_.first;
}

file::id_t grid_2d_coordinate::y() const noexcept
{
	return this->x_y_.second;
}

bool grid_2d_coordinate::operator ==(const grid_2d_coordinate &other) const noexcept
{
	return this->x_y_==other.x_y_;
}

bool grid_2d_coordinate::operator !=(const grid_2d_coordinate &other) const noexcept
{
	return !(*this==other);
}

QPair<file::id_t, file::id_t> grid_2d_coordinate::canonical(const file::id_t &x, const file::id_t &y) noexcept
{
	auto xx=x, yy=y;
	return this->canonical(std::move(xx), std::move(yy));
}

QPair<file::id_t, file::id_t> grid_2d_coordinate::canonical(file::id_t &&x, file::id_t &&y) noexcept
{
	return x<y ? qMakePair(x, y) : qMakePair(y, x);
}


grid_1d_coordinate::grid_1d_coordinate(const file::id_t &i) noexcept
	: i_(i)
{}

grid_1d_coordinate::grid_1d_coordinate(file::id_t &&i) noexcept
	: i_(std::move(i))
{}

uint32_t grid_1d_coordinate::to_linear() const noexcept
{
	return this->i_.id();
}

file::id_t grid_1d_coordinate::index() const noexcept
{
	return this->i_;
}

grid_1d_coordinate& grid_1d_coordinate::operator ++() noexcept
{
	++this->i_;
	return *this;
}

grid_1d_coordinate& grid_1d_coordinate::operator --() noexcept
{
	--this->i_;
	return *this;
}

grid_1d_coordinate grid_1d_coordinate::operator ++(int) noexcept
{
	auto t=*this;
	++(*this);
	return t;
}

grid_1d_coordinate grid_1d_coordinate::operator --(int) noexcept
{
	auto t=*this;
	--(*this);
	return t;
}

bool grid_1d_coordinate::operator ==(const grid_1d_coordinate &other) const noexcept
{
	return this->i_==other.i_;
}

bool grid_1d_coordinate::operator !=(const grid_1d_coordinate &other) const noexcept
{
	return !(*this==other);
}

}
