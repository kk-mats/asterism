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

class matching_table final
{
public:
	class key final
	{
		key(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept;

	private:
		std::pair<std::shared_ptr<detection_result>, std::shared_ptr<detection_result>> r_;
	};

	class unit final
	{
		using value_t=std::vector<std::pair<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>>>;

		unit(const shared_vector<clone_pair> &left, const shared_vector<clone_pair> &right) noexcept;

	private:
		static inline float threshold_=0.8f;
		value_t matching_list_;

		bool better(const float ok_v, const float good_v, QPair<float, float> &&ok_good_max, const float t) const noexcept;
		std::unordered_map<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>> map_unidirectionally(const shared_vector<clone_pair> &g1, const shared_vector<clone_pair> &g2) const noexcept;
		void map_mutually(const shared_vector<clone_pair> &left, const shared_vector<clone_pair> &right) noexcept;
	};

	void update(const shared_list<detection_result> &results) noexcept;

	bool exists_matching_pair_of(const std::shared_ptr<clone_pair> &p) const noexcept;

private:
	std::unordered_map<key, unit> values_;
};


}

#endif // MATCHING_TABLE_HPP
