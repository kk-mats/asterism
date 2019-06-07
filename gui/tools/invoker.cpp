#include "invoker.hpp"

namespace asterism
{
QProcess* invoker::execute() noexcept
{
	this->process_->setArguments(this->args_);
	this->process_->start();
	return this->process_;
}

QString invoker::tool_name() const noexcept
{
	return QString();
}

invoker::invoker() noexcept
{}

ccfinderx_invoker::ccfinderx_invoker(const QString &dirname, const QString &output, const QString &lang, const int b, const int t, const bool f, const bool w, const int threads) noexcept
{
	QString ws=f ? "f+" : "f-";
	ws+=w ? "w+" : "w-";
	args_<<"d"<<lang<<"-o"<<output<<"-b"<<QString::number(b)<<"-t"<<QString::number(t)<<"-w"<<ws<<"-d"<<dirname<<"--threads"<<QString::number(threads);
}

QString ccfinderx_invoker::tool_name() const noexcept
{
	return clone_detector::ccfinderx.name();
}

ccvolti_invoker::ccvolti_invoker(const QString &dirname, const QString &lang, const QString &output, const double sim, const int size, const int sizeb, const int t) noexcept
{
	this->process_->setProgram("java");
	const auto oc=output+".csv";
	const auto ocs=output+".txt";
	this->args_<<"-jar"<<global_settings::instance().ccvolti()<<"-d"<<dirname<<"-l"<<lang<<"-oc"<<oc<<"-ocs"<<ocs<<"--sim"<<QString::number(sim)<<"--size"<<QString::number(size)<<"--sizeb"<<QString::number(sizeb)<<"-t"<<QString::number(t);
}

QString ccvolti_invoker::tool_name() const noexcept
{
	return clone_detector::ccvolti.name();
}


QString ccfindersw_invoker::tool_name() const noexcept
{
	return clone_detector::ccfindersw.name();
}

QString nicad_invoker::tool_name() const noexcept
{
	return clone_detector::nicad.name();
}

}