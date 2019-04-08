#include "detection_results.hpp"

namespace asterism
{

detection_results::detection_results() noexcept
{}

detection_results::detection_results(const QString &target_path) noexcept
	: target_path_(target_path)
{}

file::id_t detection_results::add(file &&file) noexcept
{
	const auto id=file.id();
	this->file_table_[id]=std::move(file);
	return id;
}

detection_result::id_t detection_results::add(const detection_result &result) noexcept
{
	const auto id=result.id();
	this->result_table_[id]=result;
	return id;
}

std::optional<heatmap_layer> detection_results::clone_pair_size_heatmap(const detection_result::id_t &id) const noexcept
{
	return heatmap_layer::colorized_by_clone_pair_size(this->result_table_[id].clone_pair_layer());
}

QList<detection_result::id_t> detection_results::result_ids() const noexcept
{
	return this->result_table_.keys();
}

bool detection_results::contains(const detection_result::id_t &id) const noexcept
{
	return this->result_table_.contains(id);
}

QString detection_results::target_path() const noexcept
{
	return this->target_path_;
}

const QHash<file::id_t, file>& detection_results::file_table() const noexcept
{
	return this->file_table_;
}

const QHash<detection_result::id_t, detection_result>& detection_results::result_table() const noexcept
{
	return this->result_table_;
}

detection_result& detection_results::operator [](const detection_result::id_t &id) noexcept
{
	return this->result_table_[id];
}

const detection_result detection_results::operator [](const detection_result::id_t &id) const noexcept
{
	return this->result_table_[id];
}

void detection_results::set_target_path(const QString &target_path) noexcept
{
	this->target_path_=target_path;
}

}
