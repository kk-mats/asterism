#ifndef CLONE_PAIR_GRID_LAYER_HPP
#define CLONE_PAIR_GRID_LAYER_HPP

#include <memory>

#include <QMap>
#include <QHash>
#include <QList>

#include "file_separated_grid_layer.hpp"
#include "model/clone_pair.hpp"

namespace asterism
{

class clone_pair_grid_layer final
	: public file_separated_grid_layer<shared_vector<clone_pair>>
{
public:
	clone_pair_grid_layer() noexcept;
	clone_pair_grid_layer(const shared_set<clone_pair> &clone_pairs, const std::shared_ptr<file_index> &file_index) noexcept;

	void update(const shared_set<clone_pair> &clone_pairs, const std::shared_ptr<file_index> &file_index) noexcept;

private:
	void make_layer(const shared_set<clone_pair> &clone_pairs, const std::shared_ptr<file_index> &file_index) noexcept;
};

}
#endif // CLONE_PAIR_GRID_LAYER_HPP
