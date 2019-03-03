#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <QFileInfo>


namespace asterism
{

QString to_canonical_file_path(const QString &path) noexcept
{
	return QFileInfo(path).canonicalFilePath();
}

QString to_canonical_path(const QString &path) noexcept
{
	return QFileInfo(path).canonicalPath();
}

}


#endif // UTILITY_HPP
