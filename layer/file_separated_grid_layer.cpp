#include "file_separated_grid_layer.hpp"

namespace asterism
{
grid_coordinate::grid_coordinate(const file::id_t &x, const file::id_t &y) noexcept
	: x_y_(this->canonical(x, y))
{}

grid_coordinate::grid_coordinate(file::id_t &&x, file::id_t &&y) noexcept
	: x_y_(this->canonical(std::move(x), std::move(y)))
{}

uint32_t grid_coordinate::to_1d() const noexcept
{
	return this->x_y_.first.id()+this->x_y_.second.id()*(this->x_y_.second.id()+1)/2;
}

file::id_t grid_coordinate::x() const noexcept
{
	return this->x_y_.first;
}

file::id_t grid_coordinate::y() const noexcept
{
	return this->x_y_.second;
}

QPair<file::id_t, file::id_t> grid_coordinate::canonical(const file::id_t &x, const file::id_t &y) noexcept
{
	auto xx=x, yy=y;
	return this->canonical(std::move(xx), std::move(yy));
}

QPair<file::id_t, file::id_t> grid_coordinate::canonical(file::id_t &&x, file::id_t &&y) noexcept
{
	return x<y ? qMakePair(x, y) : qMakePair(y, x);
}

}
