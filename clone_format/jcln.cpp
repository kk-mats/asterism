#include "jcln.hpp"

namespace asterism
{


std::optional<detection_result> jcln::parse(const QString &path) noexcept
{
	QFile file(path);

	if(QFile file(path); !file.open(QIODevice::ReadOnly))
	{
		return std::nullopt;
	}
}

}
