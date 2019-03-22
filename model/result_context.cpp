#include "result_context.hpp"

namespace asterism
{

result_context::result_context():tool_(tool::undefined)
{}

result_context::result_context(const result_context &other) noexcept
	:tool_(other.tool_), source_(other.source_)
{}

result_context::result_context(const QString &tool, const QString &source) noexcept
	:tool_(this->from_string(tool)), source_(source)
{}

result_context::result_context(const tool &tool, const QString &source) noexcept
	:tool_(tool), source_(source)
{}

QString result_context::source() const noexcept
{
	return this->source_;
}

QString result_context::tool_string() const noexcept
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

tool result_context::from_string(const QString &tool) const noexcept
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
