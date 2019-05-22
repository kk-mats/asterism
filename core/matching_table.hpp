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

class query final
{
public:
	query(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &body) noexcept;

	std::shared_ptr<detection_result> result() const noexcept;
	std::shared_ptr<clone_pair> body() const noexcept;

	bool operator ==(const query &other) const noexcept;
	
	friend uint qHash(const query &key, uint seed) noexcept;

private:
	std::shared_ptr<detection_result> result_;
	std::shared_ptr<clone_pair> body_;
};

uint qHash(const query &key, uint seed) noexcept;

class response final
{
public:
	response(const std::shared_ptr<detection_result> &result, const shared_vector<clone_pair> &clone_pairs) noexcept;

	std::shared_ptr<detection_result> result() const noexcept;
	int size() const noexcept;
	shared_vector<clone_pair>::const_iterator begin() const noexcept;
	shared_vector<clone_pair>::const_iterator end() const noexcept;

	std::shared_ptr<clone_pair> operator [](const int i) const noexcept;

private:
	std::shared_ptr<detection_result> result_;
	shared_vector<clone_pair> clone_pairs_;
};

class matching_table final
{
public:
	class key final
	{
	public:
		key(const key &k) noexcept;
		key(key &&k) noexcept;
		key(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept;

		std::shared_ptr<detection_result> left() const noexcept;
		std::shared_ptr<detection_result> right() const noexcept;

		key& operator =(const key &other) noexcept;
		key& operator =(key &&other) noexcept;
		bool operator ==(const key &other) const noexcept;

	private:
		std::pair<std::shared_ptr<detection_result>, std::shared_ptr<detection_result>> r_;
	};

	class unit final
	{
	public:
		using value_t=std::vector<std::pair<std::shared_ptr<clone_pair>, std::shared_ptr<clone_pair>>>;

		unit(const unit &u) noexcept;
		unit(const std::shared_ptr<detection_result> &left, const std::shared_ptr<detection_result> &right) noexcept;

		unit& operator =(const unit &other) noexcept;
		unit& operator =(unit &&other) noexcept;

		shared_vector<clone_pair> matched_pair(const std::shared_ptr<clone_pair> &p, const bool search_left) const noexcept;
		void update() noexcept;

		shared_vector<clone_pair> matched_in_left() const noexcept;
		shared_vector<clone_pair> matched_in_right() const noexcept;

		key unit_key() const noexcept;

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
	void append(const shared_vector<detection_result> &results) noexcept;
	void remove(const std::shared_ptr<detection_result> &result) noexcept;

	std::vector<response> matched_pair(const query &q) const noexcept;
	int count_matching_pair(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &p) const noexcept;
	bool has_matching_pair(const std::shared_ptr<detection_result> &result, const std::shared_ptr<clone_pair> &p) const noexcept;

private:
	shared_vector<detection_result> results_;
	std::vector<std::pair<key, unit>> values_;
};

}


#endif // MATCHING_TABLE_HPP
