#ifndef DETECTION_RESULT_HPP
#define DETECTION_RESULT_HPP

#include <QVector>
#include <QHash>
#include <QJsonArray>

#include "result_environment.hpp"
#include "layer/clone_pair_grid_layer.hpp"

namespace asterism
{

class detection_result final
{
public:
	detection_result() noexcept;
	detection_result(result_environment &&context, shared_set<clone_pair> &&clone_pairs) noexcept;

	clone_pair_grid_layer to_layer(const shared_list<file> &header) const noexcept;

	const result_environment& context() const noexcept;
	shared_set<clone_pair>& clone_pairs() noexcept;
	const shared_set<clone_pair>& clone_pairs() const noexcept;

private:
	result_environment context_;
	shared_set<clone_pair> clone_pairs_;
};

}
#endif // DETECTION_RESULT_HPP
