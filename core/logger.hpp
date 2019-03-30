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


void asterism_message_output(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
	QByteArray localMsg=message.toLocal8Bit();
	const char *file=context.file ? context.file : "";
	const char *function=context.function ? context.function : "";
	switch(type)
	{
		case QtDebugMsg:
			fprintf(stderr, "[Debug] at %s in %s(%u) - %s\n", file, function, context.line, localMsg.constData());
			break;
		case QtInfoMsg:
			fprintf(stderr, "[Info] at %s in %s(%u) - %s\n", file, function, context.line, localMsg.constData());
			break;
		case QtWarningMsg:
			fprintf(stderr, "[Warn] at %s in %s(%u) - %s\n", file, function, context.line, localMsg.constData());
			break;
		case QtCriticalMsg:
			fprintf(stderr, "[Critical] at %s in %s(%u) - %s\n", file, function, context.line, localMsg.constData());
			break;
		case QtFatalMsg:
			fprintf(stderr, "[Fatal] at %s in %s(%u) - %s\n", file, function, context.line, localMsg.constData());
			break;
	}
}

}

#endif // LOGGER_HPP
