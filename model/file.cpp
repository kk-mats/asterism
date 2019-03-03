#include "file.hpp"


namespace asterism
{

file::file(const QString &canonical_file_path) noexcept
	: id_(new_id()), canonical_file_path_(canonical_file_path)
{}

file::file(QString &&canonical_file_path) noexcept
	: id_(new_id()), canonical_file_path_(std::move(canonical_file_path))
{}

QString file::canonical_file_path() const noexcept
{
	return this->canonical_file_path_;
}

file::id_t file::id() const noexcept
{
	return this->id_;
}

bool file::operator ==(const QString &path) const
{
	return this->canonical_file_path_==to_canonical_file_path(path);
}

QJsonValue file::to_qjson() const noexcept
{
	return QJsonObject
	{
		{"file_id", this->id_},
		{"path", this->canonical_file_path_}
	};
}

uint32_t file::id_ctr_=0;

file::id_t file::new_id() noexcept
{
	auto id=file::id_t(id_ctr_);
	++id_ctr_;
	return id;
}

}

