#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <QString>
#include <QDir>

namespace asterism
{



enum class tool
{
	undefined, ccvolti, ccfinderx, ccfindersw, nicad
};

class result_context
{
public:
	result_context();
	result_context(const result_context &) noexcept;
	result_context(result_context &&) noexcept;
	result_context(const tool &tool, const QString &source) noexcept;

	QString source() const noexcept;
	QString tool_string() const noexcept;

protected:
	tool tool_;
	QString source_;
};

}

#endif // CONTEXT_HPP
