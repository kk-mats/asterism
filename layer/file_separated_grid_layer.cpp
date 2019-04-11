#include "file_separated_grid_layer.hpp"

namespace asterism
{

grid_2d_coordinate::grid_2d_coordinate(const std::weak_ptr<file> &x, const std::weak_ptr<file> &y) noexcept
	: x_y_(this->canonical(x, y))
{}

int grid_2d_coordinate::to_linear(const std::weak_ptr<file_index> &file_index_ptr) const noexcept
{
	const auto fi=file_index_ptr.lock();
	const auto x=(*fi)[this->x_y_.first], y=(*fi)[this->x_y_.second];
	return x+y*(y+1)/2;
}

grid_1d_coordinate grid_2d_coordinate::to_linear(const int x, const int y) noexcept
{
	return grid_1d_coordinate(x+y*(y+1)/2);
}

std::weak_ptr<file> grid_2d_coordinate::x() const noexcept
{
	return this->x_y_.first;
}

std::weak_ptr<file> grid_2d_coordinate::y() const noexcept
{
	return this->x_y_.second;
}

bool grid_2d_coordinate::operator ==(const grid_2d_coordinate &other) const noexcept
{
	return *this->x_y_.first.lock()==*other.x_y_.first.lock() && *this->x_y_.second.lock()==*other.x_y_.second.lock();
}

bool grid_2d_coordinate::operator !=(const grid_2d_coordinate &other) const noexcept
{
	return !(*this==other);
}

std::pair<std::weak_ptr<file>, std::weak_ptr<file>> grid_2d_coordinate::canonical(const std::weak_ptr<file> &x, const std::weak_ptr<file> &y) noexcept
{
	auto xx=x, yy=y;
	return this->canonical(std::move(xx), std::move(yy));
}

std::pair<std::weak_ptr<file>, std::weak_ptr<file>> grid_2d_coordinate::canonical(std::weak_ptr<file> &&x, std::weak_ptr<file> &&y) noexcept
{
	return *(x.lock())<*(y.lock()) ? std::make_pair(x, y) : std::make_pair(y, x);
}


grid_1d_coordinate::grid_1d_coordinate(const int i) noexcept
	: i_(i)
{}

int grid_1d_coordinate::to_linear(const std::weak_ptr<file_index> &file_index[[maybe_unused]]) const noexcept
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
