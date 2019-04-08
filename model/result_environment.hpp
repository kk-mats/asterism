#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <QString>
#include <QHash>

namespace asterism
{


class clone_detector final
{
public:
	clone_detector(const QString &name) noexcept;

	QString name() const noexcept;

	bool operator ==(const QString &clone_detector_name) const noexcept;

	static const clone_detector undefined;
	static const clone_detector ccvolti;
	static const clone_detector ccfinderx;
	static const clone_detector ccfindersw;
	static const clone_detector nicad;

	static clone_detector from_string(const QString &clone_detector_name) noexcept;

private:
	QString name_;

};

enum class tool
{
	undefined, ccvolti, ccfinderx, ccfindersw, nicad
};

class result_environment final
{
public:
	result_environment();
	result_environment(const result_environment &) noexcept;
	result_environment(const QString &clone_detector_name, const QString &source) noexcept;
	result_environment(const clone_detector &clone_detector, const QString &source) noexcept;

	QString source() const noexcept;
	QString clone_detector_string() const noexcept;
	QHash<QString, QString> parameters() const noexcept;

private:
	clone_detector clone_detector_;
	QString source_;
	QHash<QString, QString> parameters_;
};

}

#endif // CONTEXT_HPP
