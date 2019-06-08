#ifndef CCVOLTI_HPP
#define CCVOLTI_HPP

#include <QString>
#include <QHash>
#include <QTextStream>

#include "format_tags.hpp"
#include "core/logger.hpp"
#include "core/detection_results.hpp"

namespace asterism
{

class ccvolti final
	: public format_tags
{
public:
	static std::shared_ptr<detection_result> read(const QString &path, detection_results &results) noexcept;

private:
	class reader final
	{
	public:
		explicit reader(QFile &file) noexcept;
		std::shared_ptr<detection_result> read(const QString &path, detection_results &results) noexcept;
	
	private:
		bool read_header() noexcept;
		std::shared_ptr<clone_pair> read_line(detection_results &results) noexcept;
		std::optional<fragment> read_fragment(const int class_name, const int start_line, const int end_line, const QStringList &line, detection_results &results) const noexcept;

		QTextStream is_;
		int a_class_name_, b_class_name_;
		int a_start_line_, a_end_line_;
		int b_start_line_, b_end_line_;
		int similarity_;
	};
};

}


#endif // CCVOLTI_HPP
