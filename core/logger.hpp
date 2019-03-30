#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QtDebug>

namespace asterism
{

class message_code
{
public:
	static inline const QString file_not_found="file not found";
	static inline const QString invalid_file_format="invalid file format";

};


void asterism_message_output(QtMsgType type, const QMessageLogContext &context, const QString &message) noexcept;

}

#endif // LOGGER_HPP
