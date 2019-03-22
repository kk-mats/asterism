#ifndef CLONE_PAIR_GRID_LAYER_HPP
#define CLONE_PAIR_GRID_LAYER_HPP

#include "file_separated_grid_layer.hpp"
#include "model/clone_pair.hpp"

namespace asterism
{

class clone_pair_grid_layer final
	: public file_separated_grid_layer<QVector<clone_pair>>
{
public:
	clone_pair_grid_layer(const QList<clone_pair> &clone_pairs, const uint32_t width) noexcept;

private:

};

}
#endif // CLONE_PAIR_GRID_LAYER_HPP
