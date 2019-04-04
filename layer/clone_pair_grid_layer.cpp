#include "clone_pair_grid_layer.hpp"

namespace asterism
{

clone_pair_grid_layer::clone_pair_grid_layer() noexcept
{}

clone_pair_grid_layer::clone_pair_grid_layer(const QList<clone_pair> &clone_pairs, const uint32_t width) noexcept
	: file_separated_grid_layer(width)
{
	for(const auto &p:clone_pairs)
	{
		this->values_[grid_2d_coordinate(p.fragment1().file_id(), p.fragment2().file_id()).to_linear()].append(p);
	}
}


void clone_pair_grid_layer::make_layer(const QList<clone_pair> &clone_pairs, const uint32_t width) noexcept
{
	this->width_=width;
	for(const auto &p:clone_pairs)
	{
		this->values_[grid_2d_coordinate(p.fragment1().file_id(), p.fragment2().file_id()).to_linear()].append(p);
	}
}

}
