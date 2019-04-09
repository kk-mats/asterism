#include "file.hpp"


namespace asterism
{

file::file() noexcept
	: canonical_file_path_("invalid_constructor_call")
{}

file::file(const QString &canonical_file_path) noexcept
	: canonical_file_path_(canonical_file_path)
{}

file::file(QString &&canonical_file_path) noexcept
	: canonical_file_path_(std::move(canonical_file_path))
{}

file::file(const id_t id, const QString &canonical_file_path) noexcept
	: canonical_file_path_(canonical_file_path)
{}

file::file(const id_t id, QString &&canonical_file_path) noexcept
	: canonical_file_path_(std::move(canonical_file_path))
{}

QString file::canonical_file_path() const noexcept
{
	return this->canonical_file_path_;
}

file::id_t file::id() const noexcept
{
	return this->id_;
}

bool file::operator ==(const QString &path) const noexcept
{
	return this->canonical_file_path_==to_canonical_file_path(path);
}

bool file::operator ==(const file &other) const noexcept
{
	return this->id_==other.id_;
}

file::id_t file::new_id() noexcept
{
	auto id=file::id_t(id_ctr_);
	++id_ctr_;
	return id;
}

uint qHash(const file &key, uint seed) noexcept
{
	return qHash(key.canonical_file_path_, seed);
}

}

