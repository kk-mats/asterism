#ifndef EXTERNAL_TOOLS_SETTING_DIALOG_HPP
#define EXTERNAL_TOOLS_SETTING_DIALOG_HPP

#include <QDialog>
#include <QDialogButtonBox>
#include <QStackedWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>

#include "core/global_settings.hpp"
#include "model/result_environment.hpp"

namespace asterism
{

class clone_detector_page
	: public QDialog
{
	Q_OBJECT
public:
	clone_detector_page(const QString &tool_name, QWidget *parent=nullptr) noexcept;
	void save() noexcept;
		
private slots:
	void set_path() noexcept;

protected:
	QHBoxLayout *path_layout_;
	QString path_text() const noexcept;

private:
	const QString tool_name_;
	QLabel *path_label_;
	QLineEdit *path_line_;
	QPushButton *browse_button_;
};


class ccfinderx_page final
	: public clone_detector_page
{
	Q_OBJECT
public:
	ccfinderx_page(QWidget *parent=nullptr) noexcept;
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

class ccfindersw_page final
	: public clone_detector_page
{
	Q_OBJECT
public:
	ccfindersw_page(QWidget *parent=nullptr) noexcept;
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
	void accept() noexcept override;

private:
	QListWidget *tools_list_widget_=new QListWidget(this);
	QStackedWidget *content_widget_=new QStackedWidget(this);
	QDialogButtonBox *button_box_=new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, this);
};

}

#endif // EXTERNAL_TOOLS_SETTING_DIALOG_HPP