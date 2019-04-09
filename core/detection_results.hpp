#ifndef DETECTION_RESULTS_HPP
#define DETECTION_RESULTS_HPP

#include <memory>

#include "matching_table.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

class detection_results final
{
public:
	detection_results() noexcept;
	detection_results(const QString &target_path) noexcept;

	std::shared_ptr<file> add(QString &&canonical_file_path) noexcept;

	template<class ...Args>
	bool emplace_detection_result(Args&& ...args) noexcept;

	bool insert_result(const QString &path) noexcept;
	bool remove_result(const std::shared_ptr<detection_result> &ptr) noexcept;

	shared_list<detection_result> results() const noexcept;

	void set_target_path(const QString &target_path) noexcept;
	QString target_path() const noexcept;

private:
	QString target_path_;
	shared_set<file> files_;
	shared_set<detection_result> results_;
};

}

#endif // DETECTION_RESULTS_HPP
