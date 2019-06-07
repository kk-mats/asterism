#include "utility.hpp"

namespace asterism
{

QString to_canonical_file_path(const QString &path) noexcept
{
	return QFileInfo(QDir::fromNativeSeparators(path)).canonicalFilePath();
}

QString to_canonical_path(const QString &path) noexcept
{
	return QFileInfo(QDir::fromNativeSeparators(path)).canonicalPath();
}

}
