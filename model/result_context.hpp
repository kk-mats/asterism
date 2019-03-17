#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <QString>

namespace asterism
{


enum class tool
{
	undefined, ccvolti, ccfinderx, ccfindersw, nicad
};

class result_context final
{
public:
	result_context();
	result_context(const result_context &) noexcept;
	result_context(const QString &tool, const QString &source) noexcept;
	result_context(const tool &tool, const QString &source) noexcept;

	QString source() const noexcept;
	QString tool_string() const noexcept;

private:
	tool tool_;
	QString source_;

	tool from_string(const QString &tool) const noexcept;
};

}

#endif // CONTEXT_HPP
