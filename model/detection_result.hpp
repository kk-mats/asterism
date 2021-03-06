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

	const result_environment& environment() const noexcept;
	result_environment& environment() noexcept;

	shared_set<clone_pair>& clone_pairs() noexcept;
	const shared_set<clone_pair>& clone_pairs() const noexcept;
	std::shared_ptr<clone_pair_grid_layer> clone_pair_layer() const noexcept;

	std::shared_ptr<clone_pair_grid_layer> update_layer(const int file_size) noexcept;

	bool operator ==(const detection_result &detection_result) const noexcept;

	friend QDebug operator <<(QDebug logger, const detection_result &detection_result) noexcept;

private:
	result_environment environment_;
	shared_set<clone_pair> clone_pairs_;
	std::shared_ptr<clone_pair_grid_layer> clone_pair_grid_layer_=nullptr;
};

uint qHash(const detection_result &key, uint seed) noexcept;
uint qHash(const std::shared_ptr<detection_result> &key, uint seed) noexcept;

QDebug operator <<(QDebug logger, const detection_result &detection_result) noexcept;
}

Q_DECLARE_METATYPE(std::shared_ptr<asterism::detection_result>)

#endif // DETECTION_RESULT_HPP
