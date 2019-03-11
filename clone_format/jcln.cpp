#include "jcln.hpp"

namespace asterism
{


std::optional<detection_results> jcln::parse(const QString &path) noexcept
{
	QFile file(path);

	if(QFile file(path); !file.open(QIODevice::ReadOnly))
	{
		return std::nullopt;
	}

	auto json(QFileInfo(path).suffix()=="jcln" ?
				QJsonDocument::fromJson(file.readAll()) : // file.jcln
				QJsonDocument::fromBinaryData(file.readAll())); //file.bjcln

	if(!json.isObject())
	{
		return std::nullopt;
	}

	auto j=json.object();

	if(j.contains(""))


}

}
