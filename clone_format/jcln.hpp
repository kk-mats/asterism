#ifndef JCLN_HPP
#define JCLN_HPP

#include <QDir>
#include <QJsonDocument>

#include <optional>

#include "model/detection_result.hpp"

namespace asterism
{

class jcln
{
public:
	static std::optional<detection_result> parse(const QString &path) noexcept;
	static bool write(const detection_results &results, const QString &path) noexcept;

};

}

#endif // JCLN_HPP
