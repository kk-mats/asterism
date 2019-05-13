#include "result_environment.hpp"

namespace asterism
{

clone_detector::clone_detector(const QString &name) noexcept
	: name_(name)
{}

QString clone_detector::name() const noexcept
{
	return this->name_;
}

bool clone_detector::operator ==(const QString &clone_detector_name) const noexcept
{
	return this->name_==clone_detector_name;
}

clone_detector clone_detector::from_string(const QString &clone_detector_name) noexcept
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
	return undefined;
}

const clone_detector clone_detector::undefined("undefined");
const clone_detector clone_detector::ccvolti("CCVolti");
const clone_detector clone_detector::ccfinderx("CCFinderX");
const clone_detector clone_detector::ccfindersw("CCFinderSW");
const clone_detector clone_detector::nicad("NiCAD");


result_environment::result_environment()
	: clone_detector_(clone_detector::undefined)
{}

result_environment::result_environment(const result_environment &other) noexcept
	: clone_detector_(other.clone_detector_), source_(other.source_), name_(other.name_)
{}

result_environment::result_environment(const QString &clone_detector_name, const QString &source, const QString &name) noexcept
	: clone_detector_(clone_detector::from_string(clone_detector_name)), source_(source), name_(name)
{}

result_environment::result_environment(const clone_detector &clone_detector, const QString &source) noexcept
	: clone_detector_(clone_detector), source_(source), name_(source)
{}

void result_environment::set_name(const QString &name) noexcept
{
	this->name_=name;
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
