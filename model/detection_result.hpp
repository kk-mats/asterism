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

	id_t id() const noexcept;
	result_context context() const noexcept;
	QList<clone_pair> clone_pairs() const noexcept;
	clone_pair clone_pair_of(const clone_pair::id_t &id) const noexcept;

	clone_pair::id_t add(const clone_pair &clone_pair) noexcept;
	clone_pair::id_t add(clone_pair &&clone_pair) noexcept;

	QJsonValue to_qjson() const noexcept;

private:
	id_t id_;
	result_context context_;
	QHash<clone_pair::id_t, clone_pair> clone_pair_table_;

	static uint32_t id_ctr_;
	static id_t new_id() noexcept;
};


class detection_results final
{
public:
	detection_results(const QString &target_path) noexcept;

	file::id_t add(file &&file) noexcept;
	detection_result::id_t add(detection_result &&result) noexcept;

	QJsonValue to_qjson() const noexcept;

private:
	QString taget_path_;
	QHash<file::id_t, file> file_table_;
	QHash<detection_result::id_t, detection_result> result_table_;
};

}
#endif // DETECTION_RESULT_HPP
