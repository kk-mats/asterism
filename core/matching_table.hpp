#ifndef MATCHING_TABLE_HPP
#define MATCHING_TABLE_HPP

#include <algorithm>
#include <optional>

#include <QVector>
#include <QHash>

#include "core/logger.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

/*
class matching_table_unit final
{
public:
	matching_table_unit() noexcept;
	matching_table_unit(const detection_result &left, const detection_result &right, const float t) noexcept;

	std::optional<std::shared_ptr<clone_pair>> has_left_clone_pair_of(const std::shared_ptr<clone_pair> &ptr) const noexcept;
	std::optional<std::shared_ptr<clone_pair>> has_right_clone_pair_of(const std::shared_ptr<clone_pair> &ptr) const noexcept;

	int count_left_clone_pair_of(const std::shared_ptr<clone_pair> &ptr) const noexcept;
	int count_right_clone_pair_of(const std::shared_ptr<clone_pair> &ptr) const noexcept;

	shared_vector<clone_pair> left_clone_pair_of(const std::shared_ptr<clone_pair> &ptr) const noexcept;
	shared_vector<clone_pair> right_clone_pair_of(const std::shared_ptr<clone_pair> &ptr) const noexcept;

private:
	QVector<QPair<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>>> matching_list_;

	bool better(const float ok_v, const float good_v, QPair<float, float> &&ok_good_max, const float t) const noexcept;
	QVector<QPair<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>>> unidirectional_matching(const detection_result &first, const detection_result &second, const float t) const noexcept;
	QVector<QPair<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>>> bidirectional_matching(const detection_result &left, const detection_result &right, const float t) const noexcept;
};


class matching_table final
{
public:
	class key final
	{
	public:
		key(const detection_result::id_t &key1, const detection_result::id_t &key2) noexcept;
		key(const std::pair<detection_result::id_t, detection_result::id_t> &key) noexcept;

		bool operator ==(const key &other) const noexcept;

		friend uint qHash(const matching_table::key &key, uint seed) noexcept;

	private:
		const detection_result::id_t key1_, key2_;
	};

	bool map_mutually(const QHash<detection_result::id_t, detection_result> &detection_results, const QList<detection_result::id_t> &target_ids) noexcept;

	const matching_table_unit operator [](const key &key) const noexcept;
	matching_table_unit& operator [](const key &key) noexcept;

	void set_threshold(const float threshold, const QHash<detection_result::id_t, detection_result> &detection_results) noexcept;

private:
	float threshold_=0.8f;
	QHash<key, matching_table_unit> units_;

};

uint qHash(const matching_table::key &key, uint seed) noexcept;
*/
}

#endif // MATCHING_TABLE_HPP
