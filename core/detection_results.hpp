#ifndef DETECTION_RESULTS_HPP
#define DETECTION_RESULTS_HPP

#include <iostream>

#include <QDebug>
#include <QModelIndex>
#include <memory>
#include <type_traits>
#include <unordered_set>

#include "matching_table.hpp"
#include "core/bk.hpp"
#include "model/detection_result.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

class detection_results final
{
public:
	detection_results(const QString &target_path="") noexcept;

	std::shared_ptr<file> emplace(QString &&canonical_file_path) noexcept;
	std::shared_ptr<detection_result> empalce(result_environment &&environment, shared_set<clone_pair> &&clone_pairs) noexcept;

	void update_layers() noexcept;
	bool remove(const std::shared_ptr<detection_result> &ptr) noexcept;
	const shared_list<detection_result>& results() const noexcept;
	const shared_vector<file>& files() const noexcept;
	std::shared_ptr<matching_table> matching_pair_table() const noexcept;

	detection_result fuse() noexcept;

	std::shared_ptr<file> file_at(const int index) const noexcept;

	void set_target_path(const QString &target_path) noexcept;
	QString target_path() const noexcept;

private:
	QString target_path_;
	shared_vector<file> files_;
	shared_list<detection_result> results_;
	std::shared_ptr<matching_table> matching_table_=std::make_shared<matching_table>();


	void update_file_index() noexcept;
	void remove_files() noexcept;
};

QDebug operator <<(QDebug logger, const detection_results &results) noexcept;

}


#endif // DETECTION_RESULTS_HPP
