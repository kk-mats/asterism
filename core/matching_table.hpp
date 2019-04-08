#ifndef MATCHING_PAIR_TABLE_HPP
#define MATCHING_PAIR_TABLE_HPP

#include <algorithm>
#include <optional>
#include <QMultiHash>

#include "model/detection_result.hpp"
#include "layer/clone_pair_grid_layer.hpp"

namespace asterism
{

class matching_pair_table
{
public:
	matching_pair_table(const detection_result &left, const detection_result &right, const float t) noexcept;

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

	bool better(const float ok_v, const float ok_max, const float good_v, const float good_max, const float t) const noexcept;
	QVector<QPair<clone_pair::id_t, clone_pair::id_t>> unidirectional_matching(const detection_result &first, const detection_result &second, const float t) const noexcept;
	QVector<QPair<clone_pair::id_t, clone_pair::id_t>> bidirectional_matching(const detection_result &left, const detection_result &right, const float t) const noexcept;
};

}

#endif // MATCHING_PAIR_TABLE_HPP
