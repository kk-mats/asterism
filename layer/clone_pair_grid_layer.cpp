#include "clone_pair_grid_layer.hpp"

namespace asterism
{

clone_pair_grid_layer::clone_pair_grid_layer(const detection_result &result, const uint32_t width) noexcept
	: file_separated_grid_layer(width), result_id_(result.id())
{
	for(const auto &p:result.clone_pairs())
	{
		this->values_[grid_coordinate(p.fragment1().file_id(), p.fragment2().file_id()).to_1d()].append(p);
	}
}

detection_result::id_t clone_pair_grid_layer::result_id() const noexcept
{
	return this->result_id_;
}

}
