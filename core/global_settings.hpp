#ifndef GLOBAL_SETTINGS_HPP
#define GLOBAL_SETTINGS_HPP

#include <QSettings>
#include <QVector>
#include <QTextCodec>
#include <QStringList>

#include "core/logger.hpp"
#include "model/result_environment.hpp"

namespace asterism
{

class global_settings final
{
public:
	global_settings(const global_settings &)=delete;
	global_settings(global_settings &&)=delete;
	global_settings& operator =(const global_settings &)=delete;
	global_settings& operator =(global_settings &&)=delete;

	void sync() noexcept;
	QString value(const QStringList &args) noexcept;
	void set(const QString &value, const QStringList &args) noexcept;

	void set_ccfinderx(const QString &path, const QString &naming_rule) noexcept;
	void set_nicad(const QString &path, const QString &naming_rule) noexcept;
	void set_ccvolti(const QString &path, const QString &naming_rule) noexcept;
	void set_ccfindersw(const QString &path, const QString &naming_rule) noexcept;

	QString ccfinderx() noexcept;
	QString ccvolti() noexcept;

	static global_settings& instance() noexcept;

	static const inline QString EXTERNAL_TOOLS="externalTools";
	static const inline QString EXECUTABLE_PATH="executablePath";
	static const inline QString NAMING_RULE="naming_rule";


private:
	static inline global_settings *instance_=nullptr;

	QSettings settings_;

	global_settings() noexcept;

	struct default_value final
	{
		static const inline QString NAMING_RULE="%{CD}_%{ALLKV}";
	};

	void set_clone_detector(const QString &name, const QString &path, const QString &naming_rule) noexcept;
	void begin_groups(const QStringList &args) noexcept;
	void end_groups(const QStringList &args) noexcept;
};

}


#endif // GLOBAL_SETTINGS_HPP
