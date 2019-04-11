#ifndef FILE_HPP
#define FILE_HPP

#include <QDebug>
#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "core/utility.hpp"
#include "object_id_t.hpp"

namespace asterism
{

template <class T>
uint qHash(const std::shared_ptr<T> &t, uint seed) noexcept
{
	return qHash(*t, seed);
}

template <class T>
using shared_set=QSet<std::shared_ptr<T>>;

template <class T>
using shared_list=QList<std::shared_ptr<T>>;

template <class T>
using shared_vector=QVector<std::shared_ptr<T>>;

template <class K, class V>
using shared_map=QHash<K, std::shared_ptr<V>>;

class file final
{
public:
	using id_t=object_id_t<file>;

	file() noexcept;
	file(const QString &canonical_file_path) noexcept;
	file(QString &&canonical_file_path) noexcept;

	id_t id() const noexcept;
	QString canonical_file_path() const noexcept;

	bool operator <(const file &other) const noexcept;
	bool operator ==(const QString &path) const noexcept;
	bool operator ==(const file &other) const noexcept;

	friend QDebug operator <<(QDebug logger, const file &file) noexcept;

	friend uint qHash(const file &key, uint seed) noexcept;

private:
	id_t id_;
	QString canonical_file_path_;

	static inline uint32_t id_ctr_=0;
	static id_t new_id() noexcept;
};

uint qHash(const file &key, uint seed) noexcept;
uint qHash(const std::weak_ptr<file> &key, uint seed) noexcept;
uint qHash(const std::shared_ptr<file> &key, uint seed) noexcept;

bool operator ==(const std::weak_ptr<file> &lhs, const std::weak_ptr<file> &rhs) noexcept;
bool operator ==(const std::shared_ptr<file> &lhs, const std::shared_ptr<file> &rhs) noexcept;

QDebug operator <<(QDebug logger, const file &file) noexcept;
}

#endif // FILE_HPP
