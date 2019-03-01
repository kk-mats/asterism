#include "file_separated_grid_layer.hpp"

namespace asterism
{
grid_coordinate::grid_coordinate(const file::id_t &x, const file::id_t &y) noexcept
	: x_(std::min(x, y)), y_(std::max(x, y))
{}

grid_coordinate::grid_coordinate(file::id_t &&x, file::id_t &&y) noexcept
	: x_(std::min(x, y)), y_(std::max(x, y))
{}

uint32_t grid_coordinate::to_1d(const uint32_t width) const noexcept
{
	return this->y_.index()*width+this->x_.index();
}

}
