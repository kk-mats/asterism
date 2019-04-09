#ifndef CLONE_PAIR_GRID_LAYER_HPP
#define CLONE_PAIR_GRID_LAYER_HPP

#include <memory>

#include <QHash>
#include <QList>

#include "file_separated_grid_layer.hpp"
#include "model/clone_pair.hpp"

namespace asterism
{

template <class T>
using shared_set=QSet<std::shared_ptr<T>>;

template <class T>
using shared_list=QList<std::shared_ptr<T>>;

template <class T>
using shared_vector=QVector<std::shared_ptr<T>>;

template <class K, class V>
using shared_map=QMap<K, std::shared_ptr<V>>;

class clone_pair_grid_layer final
	: public file_separated_grid_layer<shared_vector<clone_pair>>
{
public:
	clone_pair_grid_layer() noexcept;
	clone_pair_grid_layer(const shared_set<clone_pair> &clone_pairs, const uint32_t width) noexcept;

	void make_layer(const QList<clone_pair> &clone_pairs, const uint32_t width) noexcept;
};

}
#endif // CLONE_PAIR_GRID_LAYER_HPP
