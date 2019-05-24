#ifndef INVOKER_HPP
#define INVOKER_HPP

#include <QString>
#include <QStringList>
#include <QProcess>

#include <variant>
#include <thread>

namespace asterism
{

class invoker
{
public:
	virtual void invoke(const QString &exe_path) noexcept=0;

protected:
	QStringList args_;
};

class ccfinderx_invoker final
	: public invoker
{
public:
	ccfinderx_invoker(const QString &dirname, const QString &output, const QString &lang, const int b, const int t, const bool f, const bool w, const int threads) noexcept;
	void invoke(const QString &exe_path) noexcept override;
};


class ccvolti_invoker final
	: public invoker
{
public:
	ccvolti_invoker(const QString &dirname, const QString &lang, const QString &output, const double sim, const int size, const int sizeb, const int t) noexcept;
	void invoke(const QString &exe_path) noexcept override;
};


class ccfindersw_invoker final
	: public invoker
{
public:
	void invoke(const QString &exe_path) noexcept override;
};


class nicad_invoker final
	: public invoker
{
public:
	void invoke(const QString &exe_path) noexcept override;
};

}

#endif // INVOKER_HPP