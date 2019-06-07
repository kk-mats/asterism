#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <QDir>
#include <QFileInfo>


namespace asterism
{

QString to_canonical_file_path(const QString &path) noexcept;
QString to_canonical_path(const QString &path) noexcept;

}


#endif // UTILITY_HPP
