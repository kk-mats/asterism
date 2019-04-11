#ifndef JCLN_HPP
#define JCLN_HPP

#include <QJsonDocument>

#include <optional>

#include "format_tags.hpp"
#include "core/logger.hpp"
#include "core/detection_results.hpp"

namespace asterism
{

class jcln final
	: public format_tags
{
public:
	static std::optional<detection_results> read(const QString &path, const bool is_binary) noexcept;
	static bool write(const detection_results &results, const QString &path) noexcept;

private:
	class writer
	{
	public:
		QJsonValue to_qjson(const std::shared_ptr<file> &file_ptr, const QHash<std::shared_ptr<file>, int> file_index_map) noexcept;
		QJsonValue to_qjson(const fragment &fragment, const QHash<std::shared_ptr<file>, int> file_index_map) noexcept;
		QJsonValue to_qjson(const std::shared_ptr<clone_pair> &clone_pair, const QHash<std::shared_ptr<file>, int> file_index_map) noexcept;
		QJsonValue to_qjson(const std::shared_ptr<detection_result> &detection_result, const QHash<std::shared_ptr<file>, int> file_index_map) noexcept;
		QJsonValue to_qjson(const detection_results &detection_results) noexcept;
	};

	class reader
	{
	public:
		reader()=default;
		std::optional<detection_results> read(const QJsonObject &json) noexcept;

	private:
		std::optional<fragment> read_fragment(const QJsonObject &json) noexcept;
		std::optional<clone_pair> read_clone_pair(const QJsonObject &json) noexcept;
		bool read_detection_result(const QJsonObject &json) noexcept;

		detection_results results_;
		shared_map<int, file> id_file_ptr_map_;
	};
};

}

#endif // JCLN_HPP
