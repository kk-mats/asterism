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
	static std::optional<detection_results> read(const QString &path) noexcept;
	static bool write(const detection_results &results, const QString &path) noexcept;

private:
	class writer
	{
	public:
		writer() noexcept=default;
		QJsonValue to_qjson(const detection_results &detection_results) noexcept;

	private:
		QJsonValue to_qjson(const std::shared_ptr<file> &file_ptr) noexcept;
		QJsonValue to_qjson(const fragment &fragment) noexcept;
		QJsonValue to_qjson(const std::shared_ptr<clone_pair> &clone_pair) noexcept;
		QJsonValue to_qjson(const std::shared_ptr<detection_result> &detection_result) noexcept;
	};

	class reader
	{
	public:
		reader() noexcept=default;
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
