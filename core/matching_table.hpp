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


class matching_table_unit final
{
public:
	matching_table_unit() noexcept;
	matching_table_unit(const detection_result &left, const detection_result &right, const float t) noexcept;

	std::optional<clone_pair::id_t> has_left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept;
	std::optional<clone_pair::id_t> has_right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept;

	int count_left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept;
	int count_right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept;

	detection_result::id_t left_result_id() const noexcept;
	detection_result::id_t right_result_id() const noexcept;

	QVector<clone_pair::id_t> left_clone_pair_of(const clone_pair::id_t &right_clone_pair_id) const noexcept;
	QVector<clone_pair::id_t> right_clone_pair_of(const clone_pair::id_t &left_clone_pair_id) const noexcept;

private:
	detection_result::id_t left_result_id_, right_result_id_;
	QVector<QPair<clone_pair::id_t, clone_pair::id_t>> matching_list_;

	bool better(const float ok_v, const float good_v, QPair<float, float> &&ok_good_max, const float t) const noexcept;
	QVector<QPair<clone_pair::id_t, clone_pair::id_t>> unidirectional_matching(const detection_result &first, const detection_result &second, const float t) const noexcept;
	QVector<QPair<clone_pair::id_t, clone_pair::id_t>> bidirectional_matching(const detection_result &left, const detection_result &right, const float t) const noexcept;
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

}

#endif // MATCHING_TABLE_HPP
