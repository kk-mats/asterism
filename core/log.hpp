#ifndef LOG_HPP
#define LOG_HPP

#include <QString>
#include <QTextStream>

namespace asterism
{

class log
{
public:
	struct redirection_stdout_
	{};

	struct redirection_file_
	{};

	static redirection_stdout_ redirection_stdout;
	static redirection_file_ redirection_file;

	log(const log &)=delete;
	log& operator =(const log &)=delete;
	log(log &&)=delete;
	log& operator =(log &&)=delete;

	static log& instance(const redirection_stdout_) noexcept;
	static log& instance(const redirection_file_) noexcept=delete;

	void fatal(const QString &message) noexcept;
	void error(const QString &message) noexcept;
	void warn(const QString &message) noexcept;
	void info(const QString &message) noexcept;
	void debug(const QString &message) noexcept;


private:
	log(const redirection_stdout_) noexcept;
	log(const redirection_file_) noexcept=delete;

	QTextStream ts_;


	void output(const QString &message) noexcept;

};


}

#endif // LOG_HPP
