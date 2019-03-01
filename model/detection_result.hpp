#ifndef CODE_CLONE_DETECTION_RESULT_HPP
#define CODE_CLONE_DETECTION_RESULT_HPP

#include <QVector>
#include <QJsonArray>

#include "result_context.hpp"
#include "clone_pair.hpp"

namespace asterism
{

class detection_result
{
public:
	using id_t=object_id_t<detection_result>;

	detection_result() noexcept;

	result_context context() const noexcept;
	QVector<clone_pair> clone_pairs() const noexcept;

	uint32_t add(const clone_pair &clone_pair) noexcept;
	uint32_t add(clone_pair &&clone_pair) noexcept;

	QJsonValue to_qjson() const noexcept;

private:
	id_t id_;
	result_context context_;
	QVector<clone_pair> clone_pairs_;

	static uint32_t id_ctr_;
	static id_t new_id() noexcept;
};

}
#endif // CODE_CLONE_DETECTION_RESULT_HPP
