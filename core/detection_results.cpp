#include "detection_results.hpp"

namespace asterism
{

detection_results::detection_results() noexcept
	: detection_results("")
{
}

detection_results::detection_results(const QString &target_path) noexcept
	: target_path_(target_path)
{
	clone_pair_grid_layer::file_index_ptr=this->file_index_ptr_;
}

std::shared_ptr<file> detection_results::emplace(QString &&canonical_file_path) noexcept
{
	auto itr=std::find_if(this->files_.begin(), this->files_.end(), [&](const auto &f){ return f->canonical_file_path()==canonical_file_path; });
	if(itr==this->files_.end())
	{
		itr=this->files_.insert(std::make_shared<file>(std::move(canonical_file_path)));
	}
	return *itr;
}

std::shared_ptr<detection_result> detection_results::empalce(result_environment &&environment, shared_set<clone_pair> &&clone_pairs) noexcept
{
	auto itr=std::find_if(this->results_.begin(), this->results_.end(), [&](const auto &r){ return r->environment()==environment; });
	if(itr==this->results_.end())
	{
		itr=this->results_.insert(std::make_shared<detection_result>(std::move(environment), std::move(clone_pairs)));
	}
	return *itr;
}

void detection_results::update() noexcept
{
	this->update_file_index_ptr();
	std::for_each(this->results_.begin(), this->results_.end(), [](auto &&r){ r->update(); });
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

const shared_set<detection_result>& detection_results::results() const noexcept
{
	return this->results_;
}

const shared_set<file>& detection_results::files() const noexcept
{
	return this->files_;
}

QString detection_results::target_path() const noexcept
{
	return this->target_path_;
}

void detection_results::set_target_path(const QString &target_path) noexcept
{
	this->target_path_=target_path;
}

const file_index& detection_results::file_index_ptr() const noexcept
{
	return *this->file_index_ptr_;
}

void detection_results::update_file_index_ptr() noexcept
{
	auto list=this->files_.toList();
	std::sort(list.begin(), list.end(), [](const auto &f1, const auto &f2){ return *f1<*f2; });

	this->file_index_ptr_->clear();
	int index=0;
	for(const auto &key:list)
	{
		this->file_index_ptr_->insert(key, index);
		++index;
	}
}

void detection_results::remove_files() noexcept
{

}


QDebug operator <<(QDebug logger, const detection_results &results) noexcept
{
	logger.nospace()<<"files :\n";
	for(const auto &file:results.files())
	{
		logger.nospace()<<"\tid="<<std::intptr_t(file.get())<<" : "<<file->canonical_file_path()<<"\n";
	}
	logger<<"results :\n";
	for(const auto &result:results.results())
	{
		logger.nospace()<<(*result)<<"\n";
	}
	return logger;
}

}
