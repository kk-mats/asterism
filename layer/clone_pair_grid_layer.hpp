#ifndef CLONE_PAIR_GRID_LAYER_HPP
#define CLONE_PAIR_GRID_LAYER_HPP

#include "file_separated_grid_layer.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class clone_pair_grid_layer final
	: public file_separated_grid_layer<QVector<clone_pair>>
{
public:
	clone_pair_grid_layer(const detection_result &result, const uint32_t width) noexcept;

	detection_result::id_t result_id() const noexcept;

private:
	detection_result::id_t result_id_;
};

}
#endif // CLONE_PAIR_GRID_LAYER_HPP
