#include "logger.hpp"

namespace asterism
{


void logger::fatal(const message_code &message_code, const QString &message) noexcept
{
	qFatal()<<"[Fatal]"<<print(message_code, message);
}

void logger::error(const message_code &message_code, const QString &message) noexcept
{
	qWarning()<<"[Warn]"<<print(message_code, message);
}

void logger::debug(const message_code &message_code, const QString &message) noexcept
{
	qDebug()<<"[Debug]"<<print(message_code, message);
}

void logger::trace(const message_code &message_code, const QString &message) noexcept
{
	qInfo()<<"[Info]"<<print(message_code, message);
}

QString logger::print(const message_code &message_code, const QString &message) noexcept
{
	QString r;
	switch(message_code)
	{
		case message_code::file_not_found : r="file not found"; break;
		case message_code::invalid_file_format : r="invalid file format"; break;
	}

	return r+message;
}

}
