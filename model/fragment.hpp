#pragma once


#include "file.hpp"

namespace asterism
{

class fragment final
{
public:
	fragment(const file::id_t &file_id, const uint32_t begin, const uint32_t end) noexcept;

	bool operator <(const fragment &other) const noexcept;

	file::id_t file_id() const noexcept;
	uint32_t begin() const noexcept;
	uint32_t end() const noexcept;

	bool from_qjson(const QJsonObject &json) noexcept;

private:
	file::id_t file_id_;
	uint32_t begin_, end_;

	static inline const QString FILE_ID="file_id";
	static inline const QString BEGIN="begin";
	static inline const QString END="end";
};

}
