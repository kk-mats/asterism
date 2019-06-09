#ifndef RESULT_ENVIRONMENT_HPP
#define RESULT_ENVIRONMENT_HPP

#include <QString>
#include <QHash>

#include "core/utility.hpp"

namespace asterism
{


class clone_detector_t final
{
public:
	clone_detector_t(const QString &name) noexcept;

	QString name() const noexcept;

	bool operator ==(const QString &clone_detector_name) const noexcept;

	static const clone_detector_t undefined;
	static const clone_detector_t ccvolti;
	static const clone_detector_t ccfinderx;
	static const clone_detector_t ccfindersw;
	static const clone_detector_t nicad;
	static const clone_detector_t ar_fuser;
	static const clone_detector_t ar_intersecter;
	static const clone_detector_t ar_uniter;

	static clone_detector_t from_string(const QString &clone_detector_name) noexcept;

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
	result_environment() noexcept;
	result_environment(const result_environment &)=default;
	result_environment(const QString &clone_detector_name, const QString &source, const QString &name) noexcept;
	result_environment(const clone_detector_t &clone_detector, const QString &source) noexcept;

	void set_name(const QString &name) noexcept;
	void add_parameter(const QString &key, const QString &value) noexcept;
	void set_parameters(const QHash<QString, QString> &parameters) noexcept;

	const clone_detector_t& clone_detector() const noexcept;
	QString name() const noexcept;
	QString source() const noexcept;
	QHash<QString, QString> parameters() const noexcept;
	
	bool operator ==(const result_environment &other) const noexcept;

private:
	clone_detector_t clone_detector_;
	QString name_;
	QString source_;
	QHash<QString, QString> parameters_;
};

}

#endif // RESULT_ENVIRONMENT_HPP
