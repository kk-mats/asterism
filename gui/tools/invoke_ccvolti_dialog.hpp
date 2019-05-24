#ifndef INVOKE_CCVOLTI_DIALOG_HPP
#define INVOKE_CCVOLTI_DIALOG_HPP

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QModelIndex>
#include <QProcess>

#include "invoke_dialog.hpp"

namespace asterism
{

class invoke_ccvolti_dialog final
	: public invoke_dialog
{
	Q_OBJECT

public:
	invoke_ccvolti_dialog(const QString &target, QWidget *parent) noexcept;

private:
	QSpinBox *size_=new QSpinBox(this);
	QSpinBox *sizeb_=new QSpinBox(this);
	QDoubleSpinBox *similarity_=new QDoubleSpinBox(this);
	threads_selector *threads_=new threads_selector(0, 1, this);

	void begin_setup_parameters_layout() noexcept override;

	invoker_t create_invoker() const noexcept override;
};

}

#endif // INVOKE_CCVOLTI_DIALOG_HPP
