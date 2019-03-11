#ifndef FILE_HPP
#define FILE_HPP

#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include <filesystem>

#include "core/utility.hpp"
#include "object_id_t.hpp"

namespace asterism
{

class file final
{
public:
	using id_t=object_id_t<file>;

	file(const QString &canonical_file_path) noexcept;
	file(QString &&canonical_file_path) noexcept;

	id_t id() const noexcept;
	QString canonical_file_path() const noexcept;

	QJsonValue to_qjson() const noexcept;

	bool operator ==(const QString &path_) const;

private:
	id_t id_;
	QString canonical_file_path_;

	static uint32_t id_ctr_;
	static id_t new_id() noexcept;

};

}

#endif // FILE_HPP
