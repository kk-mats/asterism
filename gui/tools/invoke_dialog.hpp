#ifndef INVOKE_CLONE_DETECTOR_DIALOG_HPP
#define INVOKE_CLONE_DETECTOR_DIALOG_HPP

#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "invoker.hpp"

namespace asterism
{

class threads_selector final
	: public QWidget
{
	Q_OBJECT

public:
	threads_selector(const int min, const int init, QWidget *parent=nullptr) noexcept;

	int value() const noexcept;

private slots:
	void slider_value_changed(const int i) noexcept;
	void spinbox_value_changed(const int i) noexcept;

private:
	QSlider *slider_=new QSlider(Qt::Horizontal, this);
	QSpinBox *spinbox_=new QSpinBox(this);
};

class key_arg_box final
	: public QComboBox
{
	Q_OBJECT

public:
	key_arg_box(QWidget *parent=nullptr) noexcept;

	void set_values(const std::vector<std::pair<QString, QString>> &values) noexcept;
	QString current_arg() const noexcept;
};


class invoke_dialog
	: public QDialog
{
	Q_OBJECT

public:
	invoke_dialog(const QString &target, QWidget *parent=nullptr) noexcept;
	~invoke_dialog() noexcept;

	virtual invoker_t create_invoker() const noexcept=0;

private slots:
	void get_target_path() noexcept;
	void get_output_filename() noexcept;
	void dispatch_invoker() noexcept;

signals:
	void invoker_dispatched(const invoker_t &invoker);

protected:
	QVBoxLayout *layout_=new QVBoxLayout(this);
	QLayout *parameters_layout_;

	QLineEdit *target_path_edit_=new QLineEdit(this);
	QLineEdit *output_path_edit_=new QLineEdit(this);
	key_arg_box *language_;
	
	virtual void begin_setup_parameters_layout() noexcept=0;

	void end_setup_parameters_layout() noexcept;

private:
	QLabel *target_label_=new QLabel(tr("Target:"), this);
	QPushButton *target_browse_button_=new QPushButton(tr("Browse"), this);
	QLabel *output_label_=new QLabel(tr("Output:"), this);
	QPushButton *output_browse_button_=new QPushButton(tr("Browse"), this);
	QDialogButtonBox *button_box_=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal);

	QGridLayout *directory_layout_=new QGridLayout;
};

}

#endif // INVOKE_CLONE_DETECTOR_DIALOG_HPP