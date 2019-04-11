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
	detection_result(result_environment &&environment, shared_set<clone_pair> &&clone_pairs) noexcept;

	clone_pair_grid_layer to_layer(const QMap<std::shared_ptr<file>, int> file_index_map) const noexcept;

	const result_environment& environment() const noexcept;
	shared_set<clone_pair>& clone_pairs() noexcept;
	const shared_set<clone_pair>& clone_pairs() const noexcept;

	bool operator ==(const detection_result &detection_result) const noexcept;

	friend QDebug operator <<(QDebug logger, const detection_result &detection_result) noexcept;

private:
	result_environment environment_;
	shared_set<clone_pair> clone_pairs_;
};

uint qHash(const detection_result &key, uint seed) noexcept;
uint qHash(const std::shared_ptr<detection_result> &key, uint seed) noexcept;

QDebug operator <<(QDebug logger, const detection_result &detection_result) noexcept;
}
#endif // DETECTION_RESULT_HPP
