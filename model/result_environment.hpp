#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <QString>
#include <QHash>

namespace asterism
{


enum class tool
{
	undefined, ccvolti, ccfinderx, ccfindersw, nicad
};

class result_environment final
{
public:
	result_environment();
	result_environment(const result_environment &) noexcept;
	result_environment(const QString &tool, const QString &source) noexcept;
	result_environment(const tool &tool, const QString &source) noexcept;

	QString source() const noexcept;
	QString tool_string() const noexcept;
	QHash<QString, QString> parameters() const noexcept;

private:
	tool tool_;
	QString source_;
	QHash<QString, QString> parameters_;

	tool from_string(const QString &tool) const noexcept;
};

}

#endif // CONTEXT_HPP
