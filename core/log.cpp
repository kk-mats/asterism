#include "log.hpp"

namespace asterism
{

log::log(const log::redirection_stdout_) noexcept
	: ts_(stdout)
{}

//log(const redirection_file_) noexcept;

log& log::instance(const log::redirection_stdout_) noexcept
{
	static log log(redirection_stdout);
	return log;
}

//log& instance(const redirection_file_) noexcept;

void log::fatal(const QString &message) noexcept
{
	output("[Fatal] "+message);
}

void log::error(const QString &message) noexcept
{
	output("[Error] "+message);
}

void log::warn(const QString &message) noexcept
{
	output("[Warn] "+message);
}

void log::info(const QString &message) noexcept
{
	output("[Info] "+message);
}

void log::debug(const QString &message) noexcept
{
	output("[Debug] "+message);
}

void log::output(const QString &message) noexcept
{

}

}
