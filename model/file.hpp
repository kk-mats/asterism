#ifndef FILE_HPP
#define FILE_HPP

#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "object_id_t.hpp"

namespace asterism
{

class file
{
public:
	using id_t=object_id_t<file>;

	file(const QDir path) noexcept;
	file(QDir &&path) noexcept;
	file(const id_t &id, const QDir &path) noexcept;

	QDir path() const noexcept;
	id_t id() const noexcept;

private:
	id_t id_;
	QDir path_;

	static uint32_t id_ctr_;
	static id_t new_id() noexcept;
};

}

#endif // FILE_HPP
