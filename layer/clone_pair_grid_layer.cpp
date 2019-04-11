#include "clone_pair_grid_layer.hpp"

namespace asterism
{

clone_pair_grid_layer::clone_pair_grid_layer() noexcept
{}

clone_pair_grid_layer::clone_pair_grid_layer(const shared_set<clone_pair> &clone_pairs, std::shared_ptr<file_index> &&file_index_ptr) noexcept
	: file_separated_grid_layer(std::move(file_index_ptr))
{
	this->make_layer(clone_pairs);
}


void clone_pair_grid_layer::update(const shared_set<clone_pair> &clone_pairs) noexcept
{
	this->make_layer(clone_pairs);
}

void clone_pair_grid_layer::make_layer(const shared_set<clone_pair> &clone_pairs) noexcept
{
	for(const auto &p:clone_pairs)
	{
		this->values_[grid_2d_coordinate(p->fragment1().file_ptr(), p->fragment2().file_ptr()).to_linear(file_index_ptr)].append(p);
	}
}

}
