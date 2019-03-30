#include "logger.hpp"

namespace asterism
{

void asterism_message_output(QtMsgType type, const QMessageLogContext &context, const QString &message) noexcept
{
	QByteArray localMsg=message.toLocal8Bit();
	const char *file=context.file ? context.file : "";
	const char *function=context.function ? context.function : "";
	switch(type)
	{
		case QtDebugMsg:
			fprintf(stderr, "[Debug] at %s in %s(%u) - %s\n", function, file, context.line, localMsg.constData());
			break;
		case QtInfoMsg:
			fprintf(stderr, "[Info] at %s in %s(%u) - %s\n", function, file, context.line, localMsg.constData());
			break;
		case QtWarningMsg:
			fprintf(stderr, "[Warn] at %s in %s(%u) - %s\n", function, file, context.line, localMsg.constData());
			break;
		case QtCriticalMsg:
			fprintf(stderr, "[Critical] at %s in %s(%u) - %s\n", function, file, context.line, localMsg.constData());
			break;
		case QtFatalMsg:
			fprintf(stderr, "[Fatal] at %s in %s(%u) - %s\n", function, file, context.line, localMsg.constData());
			break;
	}
}

}
