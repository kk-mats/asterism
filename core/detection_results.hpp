#ifndef DETECTION_RESULTS_HPP
#define DETECTION_RESULTS_HPP

#include <iostream>

#include <QDebug>
#include <memory>
#include <type_traits>

#include "matching_table.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

class detection_results final
{
public:
	detection_results() noexcept;
	detection_results(const QString &target_path) noexcept;

	std::shared_ptr<file> emplace(QString &&canonical_file_path) noexcept;
	std::shared_ptr<detection_result> empalce(result_environment &&environment, shared_set<clone_pair> &&clone_pairs) noexcept;

	void update() noexcept;
	bool remove(std::shared_ptr<detection_result> &&ptr) noexcept;
	const shared_list<detection_result>& results() const noexcept;
	const shared_set<file>& files() const noexcept;

	void set_target_path(const QString &target_path) noexcept;
	QString target_path() const noexcept;
	const file_index& file_index_map() const noexcept;

private:
	QString target_path_;
	shared_set<file> files_;
	shared_list<detection_result> results_;
	file_index file_index_;

	void update_file_index() noexcept;
	void remove_files() noexcept;
};

QDebug operator <<(QDebug logger, const detection_results &results) noexcept;

}

#endif // DETECTION_RESULTS_HPP
