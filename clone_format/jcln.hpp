#ifndef JCLN_HPP
#define JCLN_HPP

#include <QJsonDocument>

#include <optional>

#include "model/detection_result.hpp"

namespace asterism
{

class jcln
{
public:
	static std::optional<detection_results> read(const QString &path) noexcept;
	static bool write(const detection_results &results, const QString &path) noexcept;

private:
	static inline const QString GLOBAL="global";
	static inline const QString TARGET="target";
	static inline const QString ENVIRONMENT="environment";
	static inline const QString SOURCE="source";
	static inline const QString CLONE_DETECTOR="clone_detector";
	static inline const QString NAME="name";
	static inline const QString PARAMETERS="parameters";
	static inline const QString SIZE="size";
	static inline const QString FILE_TABLE="file_table";
	static inline const QString RESULTS="results";
	static inline const QString CLONE_PAIRS="clone_pairs";
	static inline const QString RESULT_ID="result_id";
	static inline const QString FILE_ID="file_id";
	static inline const QString PATH="path";
	static inline const QString CLONE_PAIR_ID="clone_pair_id";
	static inline const QString SIMILARITY="similarity";
	static inline const QString FRAGMENT1="fragment1";
	static inline const QString FRAGMENT2="fragment2";
	static inline const QString BEGIN="begin";
	static inline const QString END="end";

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
