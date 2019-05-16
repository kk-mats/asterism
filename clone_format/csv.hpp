#ifndef CSV_HPP
#define CSV_HPP

#include <QFile>
#include <QDir>
#include <QTextStream>

#include "format_tags.hpp"
#include "core/logger.hpp"
#include "model/detection_result.hpp"

namespace asterism
{


class csv final
	: public format_tags
{
public:
	static bool write(const detection_result &result, const QString &project_root, const QString &path) noexcept;

private:
	class writer final
	{
	public:
		writer(QFile *f, const QString &project_root) noexcept;
		bool write(const detection_result &result) noexcept;

	private:
		static const inline QVector<QString> header_={"cf1_subdirectory", "cf1_filename", "cf1_startline", "cf1_endline", "cf2_subdirectory", "cf2_filename", "cf2_endline"};
		QTextStream os_;
		QDir project_root_;

		bool write(const std::shared_ptr<clone_pair> &clone_pair) noexcept;
		bool write(const fragment &fragment) noexcept;
	};
};

}

#endif // CSV_HPP