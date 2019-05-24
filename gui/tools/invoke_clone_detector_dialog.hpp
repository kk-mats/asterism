#ifndef INVOKE_CLONE_DETECTOR_DIALOG_HPP
#define INVOKE_CLONE_DETECTOR_DIALOG_HPP

#include <QLabel>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QFormLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QProcess>

#include <thread>

namespace asterism
{

class ccvolti_invoker final
{
public:
	ccvolti_invoker(const QString &dirname, const QString &lang, const QString &output, const double sim, const int size, const int sizeb, const int t) noexcept;

	void invoke(const QString &exe_path) noexcept;

private:
	QStringList args_;
};

class invoke_ccvolti_dialog : public QDialog
{
	Q_OBJECT

public:
	invoke_ccvolti_dialog(const QString &target=QString(), QWidget *parent=nullptr);
	~invoke_ccvolti_dialog();

private slots:
	void get_target_path() noexcept;
	void get_output_filename() noexcept;

private:
	QLabel *target_label_=new QLabel(tr("Target"), this);
	QLineEdit *target_path_edit_=new QLineEdit(this);
	QPushButton *target_browse_button_=new QPushButton(tr("Browse"), this);

	QLabel *output_label_=new QLabel(tr("Output"), this);
	QLineEdit *output_path_edit_=new QLineEdit(this);
	QPushButton *output_browse_button_=new QPushButton(tr("Browse"), this);

	QComboBox *language_box_=new QComboBox(this);
	QSpinBox *size_box_=new QSpinBox(this);
	QSpinBox *sizeb_box_=new QSpinBox(this);
	QDoubleSpinBox *similarity_box_=new QDoubleSpinBox(this);
	QSpinBox *threads_box_=new QSpinBox(this);
};

}

#endif // INVOKE_CLONE_DETECTOR_DIALOG_HPP