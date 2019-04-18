#include "logger.hpp"

namespace asterism
{

error_code::error_code(const QString &base, const QString &error_code_string) noexcept
	: base_(base), error_code_string_(error_code_string)
{}


QDebug operator <<(QDebug logger, const error_code &code) noexcept
{
	logger<<QStringLiteral("when ")<<code.base_<<QStringLiteral(": ")<<code.error_code_string_;
	return logger;
}

void asterism_message_output(QtMsgType type, const QMessageLogContext &context, const QString &message) noexcept
{
	QByteArray localMsg=message.toLocal8Bit();
	const char *file=context.file ? context.file : "";
	const char *function=context.function ? context.function : "";
	switch(type)
	{
		case QtDebugMsg:
			fprintf(stderr, "[Debug] at %s in %s(%u)\n - %s\n", function, file, context.line, localMsg.constData());
			break;
		case QtInfoMsg:
			fprintf(stderr, "[Info] at %s in %s(%u)\n - %s\n", function, file, context.line, localMsg.constData());
			break;
		case QtWarningMsg:
			fprintf(stderr, "[Warn] at %s in %s(%u)\n - %s\n", function, file, context.line, localMsg.constData());
			break;
		case QtCriticalMsg:
			fprintf(stderr, "[Critical] at %s in %s(%u)\n - %s\n", function, file, context.line, localMsg.constData());
			break;
		case QtFatalMsg:
			fprintf(stderr, "[Fatal] at %s in %s(%u)\n - %s\n", function, file, context.line, localMsg.constData());
			break;
	}
}

}
