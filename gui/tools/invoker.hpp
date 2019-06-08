#ifndef INVOKER_HPP
#define INVOKER_HPP

#include <QString>
#include <QStringList>
#include <QProcess>

#include <variant>
#include <thread>

#include "core/global_settings.hpp"

namespace asterism
{

class invoker
	: public QObject
{
public:
	invoker() noexcept;
	invoker(const invoker &i) noexcept;

	QProcess* execute() noexcept;

	invoker& operator =(invoker &&invoker) noexcept;

	virtual QString tool_name() const noexcept=0;
	virtual QString clone_file() const noexcept=0;

protected:
	QStringList args_;
	QProcess *process_=new QProcess;
};

class ccfinderx_invoker final
	: public invoker
{
public:
	ccfinderx_invoker() noexcept=default;
	ccfinderx_invoker(const ccfinderx_invoker &v) noexcept=default;
	ccfinderx_invoker(ccfinderx_invoker &&v) noexcept=default;
	ccfinderx_invoker(const QString &dirname, const QString &output, const QString &lang, const int b, const int t, const bool f, const bool w, const int threads) noexcept;
	QString tool_name() const noexcept override;
	QString clone_file() const noexcept override;

	ccfinderx_invoker& operator =(ccfinderx_invoker &&) noexcept=default;
};


class ccvolti_invoker final
	: public invoker
{
public:
	ccvolti_invoker() noexcept=default;
	ccvolti_invoker(const ccvolti_invoker &v) noexcept=default;
	ccvolti_invoker(ccvolti_invoker &&v) noexcept=default;
	ccvolti_invoker(const QString &dirname, const QString &lang, const QString &output, const double sim, const int size, const int sizeb, const int t) noexcept;
	QString tool_name() const noexcept override;
	QString clone_file() const noexcept override;

	ccvolti_invoker& operator =(ccvolti_invoker &&) noexcept=default;
};


class ccfindersw_invoker final
	: public invoker
{
public:
	ccfindersw_invoker() noexcept=default;
	ccfindersw_invoker(const ccfindersw_invoker &v) noexcept=default;
	ccfindersw_invoker(ccfindersw_invoker &&v) noexcept=default;
	QString tool_name() const noexcept override;
	QString clone_file() const noexcept override;

	ccfindersw_invoker& operator =(ccfindersw_invoker &&) noexcept=default;
};


class nicad_invoker final
	: public invoker
{
public:
	nicad_invoker() noexcept=default;
	nicad_invoker(const nicad_invoker &v) noexcept=default;
	nicad_invoker(nicad_invoker &&v) noexcept=default;
	QString tool_name() const noexcept override;
	QString clone_file() const noexcept override;

	nicad_invoker& operator =(nicad_invoker &&) noexcept=default;
};

using invoker_t=std::variant<ccfinderx_invoker, ccvolti_invoker, ccfindersw_invoker, nicad_invoker>;

}

#endif // INVOKER_HPP