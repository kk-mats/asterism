#ifndef INVOKE_FINDERX_DIALOG_HPP
#define INVOKE_FINDERX_DIALOG_HPP

#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>

#include "invoke_dialog.hpp"

namespace asterism
{

class invoke_ccfinderx_dialog final
	: public invoke_dialog
{
	Q_OBJECT

public:
	invoke_ccfinderx_dialog(const QString &target, QWidget *parent) noexcept;

private:
	QSpinBox *len_=new QSpinBox(this);
	QSpinBox *tks_=new QSpinBox(this);
	QCheckBox *intra_file_clones_=new QCheckBox(tr("Detect intra-file clones (w+/w-)"), this);
	QCheckBox *inter_file_clones_=new QCheckBox(tr("Detect inter-file clones (f+/f-)"), this);
	threads_selector *threads_=new threads_selector(1, std::thread::hardware_concurrency(), this);

	void begin_setup_parameters_layout() noexcept override;
	invoker_t create_invoker() const noexcept override;
};

}

#endif // INVOKE_CCFINDERX_DIALOG_HPP
