#include "detection_results.hpp"

namespace asterism
{

detection_results::detection_results() noexcept
{}

detection_results::detection_results(const QString &target_path) noexcept
	: target_path_(target_path)
{}

std::shared_ptr<file> detection_results::add(QString &&canonical_file_path) noexcept
{
	if(auto itr=std::find(this->files_.begin(), this->files_.end(), [&](const auto &f){ return f.get()==canonical_file_path; }); itr==this->files_.end())
	{
		auto ptr=std::make_shared<file>(std::move(canonical_file_path));
		this->files_.insert(ptr);
		return ptr;
	}
	else
	{
		return *itr;
	}
}

template<class ...Args>
bool detection_results::emplace_detection_result(Args&& ...args) noexcept
{
	this->results_.insert(std::make_shared<detection_results>(std::move(args...)));
	return true;
}

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
