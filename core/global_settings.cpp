#include "global_settings.hpp"

namespace asterism
{

global_settings::global_settings() noexcept
	:settings_("asterism", QSettings::IniFormat)
{
	this->settings_.setIniCodec(QTextCodec::codecForName("UTF-8"));
	qInfo()<<this->settings_.fileName();
}

void global_settings::sync() noexcept
{
	this->settings_.sync();
}

QString global_settings::value(const QStringList &args) noexcept
{
	this->begin_groups(args);
	QString r=this->settings_.contains(args[args.size()-1]) ? this->settings_.value(args[args.size()-1]).toString() : "";
	this->end_groups(args);

	return r;
}

void global_settings::set(const QString &value, const QStringList &args) noexcept
{
	this->begin_groups(args);
	this->settings_.setValue(args[args.size()-1], value);
	this->end_groups(args);
}

void global_settings::set_ccfinderx(const QString &path, const QString &naming_rule) noexcept
{
	this->set_clone_detector(clone_detector::ccfinderx.name(), path, naming_rule);
}

void global_settings::set_nicad(const QString &path, const QString &naming_rule) noexcept
{
	this->set_clone_detector(clone_detector::nicad.name(), path, naming_rule);
}

void global_settings::set_ccvolti(const QString &path, const QString &naming_rule) noexcept
{
	this->set_clone_detector(clone_detector::ccvolti.name(), path, naming_rule);
}

void global_settings::set_ccfindersw(const QString &path, const QString &naming_rule) noexcept
{
	this->set_clone_detector(clone_detector::ccfindersw.name(), path, naming_rule);
}

global_settings& global_settings::instance() noexcept
{
	if(instance_==nullptr)
	{
		instance_=new global_settings();
	}
	return *instance_;
}


void global_settings::set_clone_detector(const QString &name, const QString &path, const QString &naming_rule) noexcept
{
	this->settings_.beginGroup(EXTERNAL_TOOLS);
	this->settings_.beginGroup(name);
	this->settings_.setValue(EXECUTABLE_PATH, path);
	this->settings_.setValue(NAMING_RULE, naming_rule);
	this->settings_.endGroup();
	this->settings_.endGroup();
}

void global_settings::begin_groups(const QStringList &args) noexcept
{
	for(int i=0; i<args.size()-1; ++i)
	{
		this->settings_.beginGroup(args[i]);
	}
}

void global_settings::end_groups(const QStringList &args) noexcept
{
	for(int i=args.size()-1; 0<=i; --i)
	{
		this->settings_.endGroup();
	}
}


}