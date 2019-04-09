#ifndef FILE_HPP
#define FILE_HPP

#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "core/utility.hpp"
#include "object_id_t.hpp"

namespace asterism
{

class file final
{
public:
	using id_t=object_id_t<file>;

	file() noexcept;
	file(const QString &canonical_file_path) noexcept;
	file(QString &&canonical_file_path) noexcept;

	file(const id_t id, const QString &canonical_file_path) noexcept;
	file(const id_t id, QString &&canonical_file_path) noexcept;

	id_t id() const noexcept;
	QString canonical_file_path() const noexcept;

	bool operator ==(const QString &path) const noexcept;
	bool operator ==(const file &other) const noexcept;

	friend uint qHash(const file &key, uint seed) noexcept;

private:
	id_t id_;
	QString canonical_file_path_;

	static inline uint32_t id_ctr_=0;
	static id_t new_id() noexcept;
};

uint qHash(const file &key, uint seed) noexcept;
}

#endif // FILE_HPP
