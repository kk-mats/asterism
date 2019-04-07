#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QtDebug>

namespace asterism
{

class error_code final
{
public:
	error_code(const QString &base, const QString &error_code_string) noexcept;

	friend QDebug operator <<(QDebug logger, const error_code &code) noexcept;

private:
	const QString base_;
	const QString error_code_string_;
};

QDebug operator <<(QDebug logger, const error_code &code) noexcept;

class code_clone_loading_error final
{
private:
	static inline const auto base=QStringLiteral("loading code clones");

public:
	static inline const auto file_not_found=error_code(base, QStringLiteral("file not found"));
	static inline const auto invalid_file_format=error_code(base, QStringLiteral("invalid file format"));
};

class heatmap_conversion_error final
{
private:
	static inline const auto base=QStringLiteral("heatmap conversion");

public:
	static inline const auto color_index_out_of_range=error_code(base, QStringLiteral("color index out of range"));
};

void asterism_message_output(QtMsgType type, const QMessageLogContext &context, const QString &message) noexcept;

}

#endif // LOGGER_HPP
