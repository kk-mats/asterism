#ifndef INVOKE_CLONE_DETECTOR_DIALOG_HPP
#define INVOKE_CLONE_DETECTOR_DIALOG_HPP

#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include <thread>

namespace asterism
{

class ccfinderx_invoker;
class ccvolti_invoker;
class ccfindersw_invoker;
class nicad_invoker;


class threads_slider final
	: public QSlider
{
public:
	threads_slider(const int min, const int init, QWidget *parent=nullptr) noexcept;
};

class language_box final
	: public QComboBox
{
public:
	language_box(QWidget *parent=nullptr) noexcept;

	void set_languages(const std::vector<std::pair<QString, QString>> &param_arg) noexcept;
	QString current_arg() const noexcept;
};

class invoke_dialog
	: public QDialog
{
	Q_OBJECT

public:
	using invoker_t=std::variant<ccfinderx_invoker, ccvolti_invoker, ccfindersw_invoker, nicad_invoker>;

	invoke_dialog(const QString &target, QWidget *parent=nullptr) noexcept;

private slots:
	void get_target_path() noexcept;
	void get_output_filename() noexcept;
	void dispatch_invoker() noexcept;

signals:
	void invoker_dispatched(const invoker_t &invoker);

protected:
	QLayout *parameters_layout_;

	QLineEdit *target_path_edit_=new QLineEdit(this);
	QLineEdit *output_path_edit_=new QLineEdit(this);
	language_box *language_=new language_box(this);

	virtual void setup_parameters_layout() noexcept=0;
	virtual invoker_t create_invoker() const noexcept=0;

private:
	QLabel *target_label_=new QLabel(tr("Target"), this);
	QPushButton *target_browse_button_=new QPushButton(tr("Browse"), this);

	QLabel *output_label_=new QLabel(tr("Output"), this);
	QPushButton *output_browse_button_=new QPushButton(tr("Browse"), this);
	
	QDialogButtonBox *button_box_=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal);

	QGridLayout *directory_layout_=new QGridLayout(this);
	QVBoxLayout *layout_=new QVBoxLayout(this);
};

}

#endif // INVOKE_CLONE_DETECTOR_DIALOG_HPP