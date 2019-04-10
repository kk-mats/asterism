#include "clone_pair_grid_layer.hpp"

namespace asterism
{

clone_pair_grid_layer::clone_pair_grid_layer() noexcept
{}

clone_pair_grid_layer::clone_pair_grid_layer(const shared_set<clone_pair> &clone_pairs, const QMap<std::shared_ptr<file>, int> file_index_map) noexcept
	: file_separated_grid_layer(file_index_map.size())
{
	for(const auto &p:clone_pairs)
	{
		auto x=file_index_map[p->fragment1().file_ptr()];
		auto y=file_index_map[p->fragment2().file_ptr()];
		this->values_[grid_2d_coordinate(x, y).to_linear()].append(p);
	}
}


void clone_pair_grid_layer::make_layer(const shared_set<clone_pair> &clone_pairs, const QMap<std::shared_ptr<file>, int> file_index_map) noexcept
{
	this->width_=file_index_map.size();
	for(const auto &p:clone_pairs)
	{
		auto x=file_index_map[p->fragment1().file_ptr()];
		auto y=file_index_map[p->fragment2().file_ptr()];
		this->values_[grid_2d_coordinate(x, y).to_linear()].append(p);
	}
}

}
