#ifndef MATCHING_PAIR_TABLE_HPP
#define MATCHING_PAIR_TABLE_HPP

#include <algorithm>
#include <optional>

#include "model/detection_result.hpp"
#include "layer/clone_pair_grid_layer.hpp"

namespace asterism
{

class matching_pair_table
{
public:
	matching_pair_table(const clone_pair_grid_layer &left, const clone_pair_grid_layer &right) noexcept;

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

	QList<QPair<clone_pair::id_t, clone_pair::id_t>> unidirectional_matching(const clone_pair_grid_layer &first, const clone_pair_grid_layer &second) const noexcept;
	QVector<QPair<clone_pair::id_t, clone_pair::id_t>> bidirectional_matching(const clone_pair_grid_layer &first, const clone_pair_grid_layer &second) const noexcept;
};

}

#endif // MATCHING_PAIR_TABLE_HPP
