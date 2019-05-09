#include "file_separated_grid_layer.hpp"

namespace asterism
{

grid_2d_coordinate::grid_2d_coordinate(const std::weak_ptr<file> &x, const std::weak_ptr<file> &y, const std::shared_ptr<file_index> &file_index) noexcept
	: x_y_(std::minmax(file_index->at(x), file_index->at(y)))
{}

int grid_2d_coordinate::to_linear() const noexcept
{
	const auto x=this->x_y_.first, y=this->x_y_.second;
	return x+y*(y+1)/2;
}

grid_1d_coordinate grid_2d_coordinate::to_linear(const int x, const int y) noexcept
{
	const auto [xx, yy]=std::minmax(x, y);
	return grid_1d_coordinate(xx+yy*(yy+1)/2);
}

int grid_2d_coordinate::x() const noexcept
{
	return this->x_y_.first;
}

int grid_2d_coordinate::y() const noexcept
{
	return this->x_y_.second;
}

bool grid_2d_coordinate::operator ==(const grid_2d_coordinate &other) const noexcept
{
	return this->x_y_.first==other.x_y_.first && this->x_y_.second==other.x_y_.second;
}

bool grid_2d_coordinate::operator !=(const grid_2d_coordinate &other) const noexcept
{
	return !(*this==other);
}


grid_1d_coordinate::grid_1d_coordinate(const int i) noexcept
	: i_(i)
{}

int grid_1d_coordinate::to_linear() const noexcept
{
	return this->i_;
}

grid_1d_coordinate &grid_1d_coordinate::operator ++() noexcept
{
	++this->i_;
	return *this;
}

grid_1d_coordinate &grid_1d_coordinate::operator --() noexcept
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