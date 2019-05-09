#include "clone_pair_grid_layer.hpp"

namespace asterism
{

clone_pair_grid_layer::clone_pair_grid_layer() noexcept
{}

clone_pair_grid_layer::clone_pair_grid_layer(const shared_set<clone_pair> &clone_pairs, const file_index &file_index) noexcept
	: file_separated_grid_layer(file_index)
{
	this->make_layer(clone_pairs, file_index);
}

void clone_pair_grid_layer::update(const shared_set<clone_pair> &clone_pairs, const file_index &file_index) noexcept
{
	this->resize(file_index.size());
	this->make_layer(clone_pairs, file_index);
}

void clone_pair_grid_layer::make_layer(const shared_set<clone_pair> &clone_pairs, const file_index &file_index) noexcept
{
	for(const auto &p:clone_pairs)
	{
		this->values_[grid_2d_coordinate(p->fragment1().file_ptr(), p->fragment2().file_ptr(), file_index).to_linear()].append(p);
	}
}

}
