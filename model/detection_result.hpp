#ifndef DETECTION_RESULT_HPP
#define DETECTION_RESULT_HPP

#include <QVector>
#include <QHash>
#include <QJsonArray>

#include "result_context.hpp"
#include "layer/clone_pair_grid_layer.hpp"

namespace asterism
{


class detection_result final
{
public:
	using id_t=object_id_t<detection_result>;

	detection_result() noexcept;
	detection_result(const id_t id, result_context &&context, QHash<clone_pair::id_t, clone_pair> &&clone_pair_table) noexcept;

	id_t id() const noexcept;
	result_context context() const noexcept;
	QList<clone_pair> clone_pairs() const noexcept;
	clone_pair operator [](const clone_pair::id_t &id) const&& noexcept;

	clone_pair::id_t add(const clone_pair &clone_pair) noexcept;
	clone_pair::id_t add(clone_pair &&clone_pair) noexcept;

	const QHash<clone_pair::id_t, clone_pair>& clone_pair_table() const noexcept;

private:
	id_t id_;
	result_context context_;
	QHash<clone_pair::id_t, clone_pair> clone_pair_table_;

	static inline uint32_t id_ctr_=0;
	static id_t new_id() noexcept;
};


class detection_results final
{
public:
	detection_results(const QString &target_path) noexcept;

	file::id_t add(file &&file) noexcept;
	detection_result::id_t add(detection_result &&result) noexcept;

	QString target_path() const noexcept;
	const QHash<file::id_t, file> file_table() const noexcept;
	const QHash<detection_result::id_t, detection_result> result_table() const noexcept;

private:
	QString target_path_;
	QHash<file::id_t, file> file_table_;
	QHash<detection_result::id_t, detection_result> result_table_;
};

}
#endif // DETECTION_RESULT_HPP
