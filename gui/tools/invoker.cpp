#include "invoker.hpp"

namespace asterism
{

invoker::invoker() noexcept
{
}

invoker::invoker(const invoker &i) noexcept
	: args_(i.args_), process_(i.process_)
{
}

QProcess* invoker::execute() noexcept
{
	this->process_->setArguments(this->args_);
	this->process_->start();
	return this->process_;
}

invoker& invoker::operator=(invoker &&invoker) noexcept
{
	this->args_=std::move(invoker.args_);
	this->process_=invoker.process_;
	invoker.process_=nullptr;
	return *this;
}

QString invoker::tool_name() const noexcept
{
	return QString();
}

ccfinderx_invoker::ccfinderx_invoker(const QString &dirname, const QString &output, const QString &lang, const int b, const int t, const bool f, const bool w, const int threads) noexcept
	: invoker()
{
	this->process_->setProgram(global_settings::instance().ccfinderx());
	QString ws=f ? "f+" : "f-";
	ws+=w ? "w+" : "w-";
	args_<<"d"<<lang<<"-o"<<output<<"-b"<<QString::number(b)<<"-t"<<QString::number(t)<<"-w"<<ws<<"-d"<<dirname<<"--threads="+QString::number(threads);
}

QString ccfinderx_invoker::tool_name() const noexcept
{
	return clone_detector_t::ccfinderx.name();
}

QString ccfinderx_invoker::clone_file() const noexcept
{
	return this->args_[3];
}

ccvolti_invoker::ccvolti_invoker(const QString &dirname, const QString &lang, const QString &output, const double sim, const int size, const int sizeb, const int t) noexcept
	: invoker()
{
	this->process_->setProgram("java");
	this->args_<<"-jar"<<global_settings::instance().ccvolti()<<"-d"<<dirname<<"-l"<<lang<<"-oc"<<output<<"--sim"<<QString::number(sim)<<"--size"<<QString::number(size)<<"--sizeb"<<QString::number(sizeb)<<"-t"<<QString::number(t);
}

QString ccvolti_invoker::tool_name() const noexcept
{
	return clone_detector_t::ccvolti.name();
}

QString ccvolti_invoker::clone_file() const noexcept
{
	return this->args_[7];
}


QString ccfindersw_invoker::tool_name() const noexcept
{
	return clone_detector_t::ccfindersw.name();
}

QString ccfindersw_invoker::clone_file() const noexcept
{
	return QString();
}

QString nicad_invoker::tool_name() const noexcept
{
	return clone_detector_t::nicad.name();
}

QString nicad_invoker::clone_file() const noexcept
{
	return QString();
}

}