#ifndef MATCHING_TABLE_HPP
#define MATCHING_TABLE_HPP

#include <algorithm>
#include <optional>
#include <unordered_map>

#include <QVector>

#include "core/logger.hpp"
#include "model/detection_result.hpp"


namespace asterism
{

class matching_table final
{
public:
	class key final
	{
	public:
		struct hash
		{
			std::size_t operator ()(const key &key) const noexcept;
		};

		key(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept;

		std::shared_ptr<detection_result> left() const noexcept;
		std::shared_ptr<detection_result> right() const noexcept;

		bool operator ==(const key &other) const noexcept;

	private:
		std::pair<std::shared_ptr<detection_result>, std::shared_ptr<detection_result>> r_;
	};

	class unit final
	{
	public:
		using value_t=std::vector<std::pair<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>>>;

		unit(const key &key) noexcept;

		int count_matching_pair(const std::shared_ptr<clone_pair> &p, const bool search_left, const std::shared_ptr<file_index> &file_index) const noexcept;
		void update() noexcept;

	private:
		static inline float threshold_=0.8f;
		key key_;
		file_separated_grid_layer<value_t> layer_;

		static bool better(const float ok_v, const float good_v, const float ok_max, const float good_max, const float t) noexcept;
		static std::unordered_map<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>> map_unidirectionally(const shared_vector<clone_pair> &g1, const shared_vector<clone_pair> &g2) noexcept;
		static value_t map_mutually(const shared_vector<clone_pair> &left, const shared_vector<clone_pair> &right) noexcept;
	};

	void update() noexcept;

	void append(const std::shared_ptr<detection_result> &result) noexcept;
	void append(const shared_list<detection_result> &results) noexcept;
	void remove(const std::shared_ptr<detection_result> &result) noexcept;

	int count_matching_pair(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &p, const std::shared_ptr<file_index> &file_index) const noexcept;
	bool has_matching_pair(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &p, const std::shared_ptr<file_index> &file_index) const noexcept;

private:
	shared_list<detection_result> results_;
	std::unordered_map<key, unit, key::hash> values_;
};

}


#endif // MATCHING_TABLE_HPP
