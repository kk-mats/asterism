#ifndef JCLN_HPP
#define JCLN_HPP

#include <QJsonDocument>

#include <optional>

#include "format_tags.hpp"
#include "core/logger.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class jcln final
	: public format_tags
{
public:
	static std::optional<detection_results> read(const QString &path) noexcept;
	static bool write(const detection_results &results, const QString &path) noexcept;

private:
	static QJsonValue to_qjson(const file &file) noexcept;
	static QJsonValue to_qjson(const fragment &fragment) noexcept;
	static QJsonValue to_qjson(const clone_pair &clone_pair) noexcept;
	static QJsonValue to_qjson(const detection_result &detection_result) noexcept;
	static QJsonValue to_qjson(const detection_results &detection_results) noexcept;

	static std::optional<fragment> read_fragment(const QJsonObject &json) noexcept;
	static std::optional<clone_pair> read_clone_pair(const QJsonObject &json) noexcept;
	static std::optional<detection_result> read_detection_result(const QJsonObject &json) noexcept;
	static std::optional<detection_results> read_detection_results(const QJsonObject &json) noexcept;

};

}

#endif // JCLN_HPP
