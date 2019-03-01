#ifndef CLONE_PAIRS_GRID_LAYER_HPP
#define CLONE_PAIRS_GRID_LAYER_HPP

#include "file_separated_grid_layer.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class clone_pairs_grid_layer final
	: public file_separated_grid_layer<QVector<clone_pair>>
{
public:
	clone_pairs_grid_layer(const QVector<clone_pair> &clone_pairs, const uint32_t width) noexcept
		: file_separated_grid_layer(width)
	{
		for(const auto &p:clone_pairs)
		{
			this->values_[grid_coordinate(p.fragment1().file_id(), p.fragment2().file_id()).to_1d(width)].append(p);
		}
	}

private:

};

}
#endif // CLONE_PAIRS_GRID_LAYER_HPP
