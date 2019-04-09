#include "detection_results.hpp"

namespace asterism
{

detection_results::detection_results() noexcept
{}

detection_results::detection_results(const QString &target_path) noexcept
	: target_path_(target_path)
{}

bool detection_results::insert_result(const QString &path) noexcept
{
	this->results_.insert()
}

bool detection_results::remove_result(const std::shared_ptr<detection_result> &ptr) noexcept
{
	bool has_removed=this->results_.remove(ptr);
}

QString detection_results::target_path() const noexcept
{
	return this->target_path_;
}

void detection_results::set_target_path(const QString &target_path) noexcept
{
	this->target_path_=target_path;
}

}
