#include "invoker.hpp"

namespace asterism
{
ccfinderx_invoker::ccfinderx_invoker(const QString &dirname, const QString &output, const QString &lang, const int b, const int t, const bool f, const bool w, const int threads) noexcept
{
	QString ws=f ? "f+" : "f-";
	ws+=w ? "w+" : "w-";
	args_<<"d"<<lang<<"-o"<<output<<"-b"<<QString::number(b)<<"-t"<<QString::number(t)<<"-w"<<ws<<"-d"<<dirname<<"--threads"<<QString::number(threads);
}

void ccfinderx_invoker::invoke(const QString &exe_path) noexcept
{

}

ccvolti_invoker::ccvolti_invoker(const QString &dirname, const QString &lang, const QString &output, const double sim, const int size, const int sizeb, const int t) noexcept
{
	const auto oc=output+".csv";
	const auto ocs=output+".txt";
	this->args_<<"-d"<<dirname<<"-l"<<lang<<"-oc"<<oc<<"-ocs"<<ocs<<"--sim"<<QString::number(sim)<<"--size"<<QString::number(size)<<"--sizeb"<<QString::number(sizeb)<<"-t"<<QString::number(t);
}

void ccvolti_invoker::invoke(const QString &exe_path) noexcept
{
	QProcess ccvolti;
	this->args_.push_front(exe_path);
	this->args_.push_front("-jar");
	ccvolti.setArguments(this->args_);
	ccvolti.start("java");
}

void ccfindersw_invoker::invoke(const QString & exe_path) noexcept
{
}

void nicad_invoker::invoke(const QString & exe_path) noexcept
{
}

}