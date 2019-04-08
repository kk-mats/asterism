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
	using id_t=object_id_t<detection_result>;

	detection_result() noexcept;
	detection_result(const id_t id, result_environment &&context, QHash<clone_pair::id_t, clone_pair> &&clone_pair_table) noexcept;

	clone_pair::id_t add(const clone_pair &clone_pair) noexcept;
	clone_pair::id_t add(clone_pair &&clone_pair) noexcept;

	void update_layer(const uint32_t layer_width) noexcept;

	clone_pair operator [](const clone_pair::id_t &id) const&& noexcept;

	id_t id() const noexcept;
	const result_environment& context() const noexcept;
	QList<clone_pair> clone_pairs() const noexcept;
	const clone_pair_grid_layer& clone_pair_layer() const noexcept;
	const QHash<clone_pair::id_t, clone_pair>& clone_pair_table() const noexcept;

private:
	id_t id_;
	result_environment context_;
	QHash<clone_pair::id_t, clone_pair> clone_pair_table_;
	clone_pair_grid_layer clone_pair_grid_layer_;

	static inline uint32_t id_ctr_=0;
	static id_t new_id() noexcept;
};

}
#endif // DETECTION_RESULT_HPP
