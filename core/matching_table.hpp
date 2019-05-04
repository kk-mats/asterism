#ifndef MATCHING_TABLE_HPP
#define MATCHING_TABLE_HPP

#include <algorithm>
#include <optional>

#include <QVector>
#include <QMultiHash>

#include "core/logger.hpp"
#include "model/detection_result.hpp"

namespace asterism
{
/*
class matching_table final
{
public:
	class key final
	{
	public:
		key(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept;

	private:
		const std::shared_ptr<detection_result> left_;
		const std::shared_ptr<detection_result> right_;
	};

	class unit final
	{
	public:
		unit() noexcept;
		unit(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept;



	private:
		QVector<std::pair<clone_pair, clone_pair>> list_;

		QVector<QPair<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>>> unidirectional_matching(const detection_result &first, const detection_result &second, const float t) const noexcept;
		QVector<QPair<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>>> bidirectional_matching(const detection_result &left, const detection_result &right, const float t) const noexcept;
	};


	bool map_mutually(const shared_vector<detection_result> &results) noexcept;
	bool remove(const std::shared_ptr<detection_result> &result) noexcept;

	const unit operator [](const key &key) const noexcept;
	unit& operator [](const key &key) noexcept;

private:
	float threshold_=0.8f;
	QHash<key, unit> units_;

};

uint qHash(const matching_table::key &key, uint seed) noexcept;

*/

}

#endif // MATCHING_TABLE_HPP
