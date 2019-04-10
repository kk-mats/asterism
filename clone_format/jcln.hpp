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
	static QJsonValue to_qjson(const std::shared_ptr<file> &file_ptr, const QHash<std::shared_ptr<file>, int> file_index_map) noexcept;
	static QJsonValue to_qjson(const fragment &fragment, const QHash<std::shared_ptr<file>, int> file_index_map) noexcept;
	static QJsonValue to_qjson(const std::shared_ptr<clone_pair> &clone_pair, const QHash<std::shared_ptr<file>, int> file_index_map) noexcept;
	static QJsonValue to_qjson(const std::shared_ptr<detection_result> &detection_result, const QHash<std::shared_ptr<file>, int> file_index_map) noexcept;
	static QJsonValue to_qjson(const detection_results &detection_results) noexcept;

	static std::optional<fragment> read_fragment(const QJsonObject &json, const shared_map<int, file> &id_file_ptr_map) noexcept;
	static std::optional<clone_pair> read_clone_pair(const QJsonObject &json, const shared_map<int, file> &id_file_ptr_map) noexcept;
	static std::optional<detection_result> read_detection_result(const QJsonObject &json, const shared_map<int, file> &id_file_ptr_map) noexcept;
	static std::optional<detection_results> read_detection_results(const QJsonObject &json) noexcept;

};

}

#endif // JCLN_HPP
