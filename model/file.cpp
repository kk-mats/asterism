#include "file.hpp"


namespace asterism
{

file::file(const QDir path) noexcept
	: id_(new_id()), path_(path)
{}

file::file(QDir &&path) noexcept
	: id_(new_id()), path_(std::move(path))
{}

file::file(const file::id_t &id, const QDir &path) noexcept
	: id_(id), path_(path)
{}

QDir file::path() const noexcept
{
	return this->path_;
}

file::id_t file::id() const noexcept
{
	return this->id_;
}

uint32_t file::id_ctr_=0;

file::id_t file::new_id() noexcept
{
	auto id=file::id_t(id_ctr_);
	++id_ctr_;
	return id;
}

}

