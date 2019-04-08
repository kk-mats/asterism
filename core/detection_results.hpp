#ifndef DETECTION_RESULTS_HPP
#define DETECTION_RESULTS_HPP

#include "matching_table.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{


class detection_results final
{
public:
	detection_results() noexcept;
	detection_results(const QString &target_path) noexcept;

	file::id_t add(file &&file) noexcept;
	detection_result::id_t add(const detection_result &result) noexcept;

	std::optional<heatmap_layer> clone_pair_size_heatmap(const detection_result::id_t &id) const noexcept;

	detection_result& operator [](const detection_result::id_t &id) noexcept;
	const detection_result operator [](const detection_result::id_t &id) const noexcept;

	QList<detection_result::id_t> result_ids() const noexcept;
	bool contains(const detection_result::id_t &id) const noexcept;

	void set_target_path(const QString &target_path) noexcept;
	QString target_path() const noexcept;
	const QHash<file::id_t, file>& file_table() const noexcept;
	const QHash<detection_result::id_t, detection_result>& result_table() const noexcept;

private:
	QString target_path_;
	QHash<file::id_t, file> file_table_;
	QHash<detection_result::id_t, detection_result> result_table_;
};

}

#endif // DETECTION_RESULTS_HPP
