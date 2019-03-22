#include "clone_pair_grid_layer.hpp"

namespace asterism
{

clone_pair_grid_layer::clone_pair_grid_layer(const QList<clone_pair> &clone_pairs, const uint32_t width) noexcept
	: file_separated_grid_layer(width)
{
	for(const auto &p:clone_pairs)
	{
		this->values_[grid_coordinate(p.fragment1().file_id(), p.fragment2().file_id()).to_1d()].append(p);
	}
}

}
