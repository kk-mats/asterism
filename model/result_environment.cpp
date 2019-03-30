#include "result_environment.hpp"

namespace asterism
{

result_environment::result_environment():tool_(tool::undefined)
{}

result_environment::result_environment(const result_environment &other) noexcept
	:tool_(other.tool_), source_(other.source_)
{}

result_environment::result_environment(const QString &tool, const QString &source) noexcept
	:tool_(this->from_string(tool)), source_(source)
{}

result_environment::result_environment(const tool &tool, const QString &source) noexcept
	:tool_(tool), source_(source)
{}

QString result_environment::source() const noexcept
{
	return this->source_;
}

QString result_environment::tool_string() const noexcept
{
	switch(this->tool_)
	{
		case tool::ccvolti: return "CCVolti";
		case tool::ccfinderx: return "CCFinderX";
		case tool::ccfindersw: return "CCFinderSW";
		case tool::nicad: return "NiCAD";
	}
	return "undefined";
}

QHash<QString, QString> result_environment::parameters() const noexcept
{
	return this->parameters_;
}

tool result_environment::from_string(const QString &tool) const noexcept
{
	if(tool=="CCVolti")
	{
		return tool::ccvolti;
	}
	else if(tool=="CCFinderX")
	{
		return tool::ccfinderx;
	}
	else if(tool=="CCFinderSW")
	{
		return tool::ccfindersw;
	}
	else if(tool=="NiCAD")
	{
		return tool::nicad;
	}
	return tool::undefined;
}

}
