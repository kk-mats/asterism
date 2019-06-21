#include "result_environment.hpp"

namespace asterism
{

clone_detector_t::clone_detector_t(const QString &name) noexcept
	: name_(name)
{}

QString clone_detector_t::name() const noexcept
{
	return this->name_;
}

bool clone_detector_t::operator ==(const QString &clone_detector_name) const noexcept
{
	return this->name_==clone_detector_name;
}

clone_detector_t clone_detector_t::from_string(const QString &clone_detector_name) noexcept
{
	if(ccvolti==clone_detector_name)
	{
		return ccvolti;
	}
	else if(ccfinderx==clone_detector_name)
	{
		return ccfinderx;
	}
	else if(ccfindersw==clone_detector_name)
	{
		return ccfindersw;
	}
	else if(nicad==clone_detector_name)
	{
		return nicad;
	}
	else if(ar_fuser==clone_detector_name)
	{
		return ar_fuser;
	}
	return undefined;
}

const clone_detector_t clone_detector_t::undefined("undefined");
const clone_detector_t clone_detector_t::ccvolti("CCVolti");
const clone_detector_t clone_detector_t::ccfinderx("CCFinderX");
const clone_detector_t clone_detector_t::ccfindersw("CCFinderSW");
const clone_detector_t clone_detector_t::nicad("NiCad");
const clone_detector_t clone_detector_t::ar_fuser("Asterism Result Fuser");


result_environment::result_environment() noexcept
	: clone_detector_(clone_detector_t::undefined)
{}

result_environment::result_environment(const QString &clone_detector_name, const QString &source, const QString &name) noexcept
	: clone_detector_(clone_detector_t::from_string(clone_detector_name)), source_(source), name_(name)
{}

result_environment::result_environment(const clone_detector_t &clone_detector, const QString &source) noexcept
	: clone_detector_(clone_detector), source_(source)
{
	this->name_=this->source_;
}

void result_environment::set_name(const QString &name) noexcept
{
	this->name_=name;
}

void result_environment::add_parameter(const QString &key, const QString &value) noexcept
{
	this->parameters_.insert(key, value);
}

void result_environment::set_parameters(const QHash<QString, QString> &parameters) noexcept
{
	this->parameters_=parameters;
}

const clone_detector_t& result_environment::clone_detector() const noexcept
{
	return this->clone_detector_;
}

QString result_environment::name() const noexcept
{
	return this->name_;
}

QString result_environment::source() const noexcept
{
	return this->source_;
}


QHash<QString, QString> result_environment::parameters() const noexcept
{
	return this->parameters_;
}

bool result_environment::operator ==(const result_environment &other) const noexcept
{
	return this->source_==other.source_;
}

}
