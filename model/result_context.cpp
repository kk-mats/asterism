#include "result_context.hpp"

namespace asterism
{

result_context::result_context():tool_(tool::undefined)
{}

result_context::result_context(const result_context &other) noexcept
	:tool_(other.tool_), source_(other.source_)
{}

result_context::result_context(result_context &&other) noexcept
	:tool_(std::move(other.tool_)), source_(std::move(other.source_))
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

}
