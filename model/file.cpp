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

QString file::canonical_file_path() const noexcept
{
	return this->canonical_file_path_;
}

int file::id() const noexcept
{
	return this->id_;
}

void file::set_id(const int id) noexcept
{
	this->id_=id;
}

bool file::operator <(const file &other) const noexcept
{
	return this->canonical_file_path_<other.canonical_file_path_;
}

bool file::operator ==(const QString &path) const noexcept
{
	return this->canonical_file_path_==to_canonical_file_path(path);
}

bool file::operator ==(const file &other) const noexcept
{
	return this->canonical_file_path_==other.canonical_file_path_;
}

uint qHash(const file &key, uint seed) noexcept
{
	return qHash(key.canonical_file_path_, seed);
}

uint qHash(const std::weak_ptr<file>& key, uint seed) noexcept
{
	return qHash(key.lock(), seed);
}

uint qHash(const std::shared_ptr<file>& key, uint seed) noexcept
{
	return qHash(key->canonical_file_path(), seed);
}
/*
bool operator ==(const std::weak_ptr<file> &lhs, const std::weak_ptr<file> &rhs) noexcept
{
	return lhs.lock()==rhs.lock();
}*/

bool operator ==(const std::shared_ptr<file> &lhs, const std::shared_ptr<file> &rhs) noexcept
{
	return *lhs==*rhs;
}

QDebug operator <<(QDebug logger, const file &file) noexcept
{
	logger.nospace()<<file.canonical_file_path_;
	return logger;
}

size_t file::hash::operator()(const std::shared_ptr<file> &f) const noexcept
{
	return std::hash<std::string>()(f->canonical_file_path().toStdString());
}

}

