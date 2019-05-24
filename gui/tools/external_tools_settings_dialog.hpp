#ifndef EXTERNAL_TOOLS_SETTING_DIALOG_HPP
#define EXTERNAL_TOOLS_SETTING_DIALOG_HPP

#include <QDialog>
#include <QStackedWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>

#include "model/result_environment.hpp"

namespace asterism
{

class clone_detector_page
	: public QDialog
{
	Q_OBJECT
public:
	clone_detector_page(const QString &init, QWidget *parent=nullptr) noexcept;
		
private slots:
	void set_path() noexcept;

protected:
	QHBoxLayout *path_layout_;

private:
	const QString init;
	QLabel *path_label_;
	QLineEdit *path_line_;
	QPushButton *browse_button_;
};


class ccfx_page final
	: public clone_detector_page
{
	Q_OBJECT
public:
	ccfx_page(QWidget *parent=nullptr) noexcept;
};

class nicad_page final
	: public clone_detector_page
{
	Q_OBJECT
public:
	nicad_page(QWidget *parent=nullptr) noexcept;
};

class ccvolti_page final
	: public clone_detector_page
{
	Q_OBJECT
public:
	ccvolti_page(QWidget *parent=nullptr) noexcept;
};

class ccsw_page final
	: public clone_detector_page
{
	Q_OBJECT
public:
	ccsw_page(QWidget *parent=nullptr) noexcept;
};


class external_tools_settings_dialog final
	: public QDialog
{
	Q_OBJECT

public:
	external_tools_settings_dialog(QWidget *parent=nullptr) noexcept;
	~external_tools_settings_dialog();

public slots:
	void change_page(QListWidgetItem *current, QListWidgetItem *previous) noexcept;

private:
	QListWidget *tools_list_widget_=new QListWidget(this);
	QStackedWidget *content_widget_=new QStackedWidget(this);
};

}

#endif // EXTERNAL_TOOLS_SETTING_DIALOG_HPP