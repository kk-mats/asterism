#include "detection_results.hpp"

namespace asterism
{

detection_results::detection_results() noexcept
{}

detection_results::detection_results(const QString &target_path) noexcept
	: target_path_(target_path)
{}

std::shared_ptr<file> detection_results::emplace(QString &&canonical_file_path) noexcept
{
	auto itr=std::find_if(this->files_.begin(), this->files_.end(), [&](const auto &f){ return f==canonical_file_path; });
	if(itr==this->files_.end())
	{
		itr=this->files_.insert(std::make_shared<file>(std::move(canonical_file_path)));
	}
	return *itr;
}

std::shared_ptr<detection_result> detection_results::empalce(result_environment &&context, shared_set<clone_pair> &&clone_pairs) noexcept
{
	auto itr=std::find_if(this->results_.begin(), this->results_.end(), [&](const detection_result &r){ return r.context().source()==context.source(); });
	if(itr==this->results_.end())
	{
		itr=this->results_.insert(std::make_shared<detection_result>(std::move(context), std::move(clone_pairs)));
	}
	return *itr;
}

bool detection_results::remove(std::shared_ptr<detection_result> &&ptr) noexcept
{
	if(auto itr=this->results_.find(ptr); itr!=this->results_.end())
	{
		ptr.reset();
		this->results_.erase(itr);
		return true;
	}
	qWarning()<<"ptr not found in detection_results::results_";
	return false;
}

QString detection_results::target_path() const noexcept
{
	return this->target_path_;
}

void detection_results::set_target_path(const QString &target_path) noexcept
{
	this->target_path_=target_path;
}

void detection_results::remove_files() noexcept
{

}

}
