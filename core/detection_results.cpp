#include "detection_results.hpp"

namespace asterism
{

detection_results::detection_results(const QString &target_path) noexcept
	: target_path_(target_path)
{
	heatmap_layer::mismatch_rate::bind(this->matching_table_);
	matched_list_model::bind(this->matching_table_);
}

std::shared_ptr<file> detection_results::emplace(QString &&canonical_file_path) noexcept
{
	auto itr=std::find_if(this->files_.begin(), this->files_.end(), [&](const auto &f){ return f->canonical_file_path()==canonical_file_path; });
	if(itr==this->files_.end())
	{
		this->files_.push_back(std::make_shared<file>(std::move(canonical_file_path)));
		itr=this->files_.end();
		--itr;
	}
	return *itr;
}

std::shared_ptr<detection_result> detection_results::empalce(result_environment &&environment, shared_set<clone_pair> &&clone_pairs) noexcept
{
	auto itr=std::find_if(this->results_.begin(), this->results_.end(), [&](const auto &r){ return r->environment()==environment; });
	if(itr==this->results_.end())
	{
		this->results_.append(std::make_shared<detection_result>(std::move(environment), std::move(clone_pairs)));
		itr=(--this->results_.end());
	}
	this->matching_table_->append(*itr);
	return *itr;
}

void detection_results::update_layers() noexcept
{
	this->update_file_index();
	for(auto &&r:this->results_)
	{
		r->update_layer(this->files_.size());
	}
	this->matching_table_->update();
}

bool detection_results::remove(const std::shared_ptr<detection_result> &ptr) noexcept
{
	if(auto itr=std::find(this->results_.begin(), this->results_.end(), (ptr)); itr!=this->results_.end())
	{
		this->matching_table_->remove(ptr);
		ptr->clone_pairs().clear();
		this->results_.erase(itr);

		this->files_.erase(std::remove_if(this->files_.begin(), this->files_.end(), [](const auto &f){ return f.use_count()==1; }), this->files_.end());
		this->update_layers();
		return true;
	}
	qWarning()<<"ptr not found in detection_results::results_";
	return false;
}

const shared_list<detection_result>& detection_results::results() const noexcept
{
	return this->results_;
}

const shared_vector<file>& detection_results::files() const noexcept
{
	return this->files_;
}

std::shared_ptr<file> detection_results::file_at(const int index) const noexcept
{
	auto itr=std::find_if(this->files_.begin(), this->files_.end(), [=](const auto &f){ return f->id()==index; });
	return itr!=this->files_.end() ? *itr : std::shared_ptr<file>(nullptr);
}

QString detection_results::target_path() const noexcept
{
	return this->target_path_;
}

void detection_results::set_target_path(const QString &target_path) noexcept
{
	this->target_path_=target_path;
}

void detection_results::update_file_index() noexcept
{
	std::vector<std::shared_ptr<file>> list(this->files_.begin(), this->files_.end());
	std::sort(list.begin(), list.end(), [](const auto &f1, const auto &f2){ return *f1<*f2; });

	int index=0;
	for(auto &&key:list)
	{
		key->set_id(index);
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
