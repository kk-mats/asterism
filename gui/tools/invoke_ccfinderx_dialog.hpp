#ifndef INVOKE_FINDERX_DIALOG_HPP
#define INVOKE_FINDERX_DIALOG_HPP

#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>

#include "invoke_dialog.hpp"

namespace asterism
{

class ccfinderx_invoker final
{
public:
	ccfinderx_invoker(const QString &dirname, const QString &output, const QString &lang, const int b, const int t, const bool f, const bool w, const int threads) noexcept;
	void invoke(const QString &exe_path) noexcept;

private:
	QStringList args_;
};

class invoke_ccfinderx_dialog final
	: public invoke_dialog
{
	Q_OBJECT

public:
	using invoke_dialog::invoke_dialog;
	using invoke_dialog::~invoke_dialog;

private:
	QSpinBox *len_=new QSpinBox(this);
	QSpinBox *tks_=new QSpinBox(this);
	QCheckBox *intra_file_clones_=new QCheckBox(tr("Detect intra-file clones (w+/w-)"), this);
	QCheckBox *inter_file_clones_=new QCheckBox(tr("Detect inter-file clones (f+/f-)"), this);
	threads_slider *threads_=new threads_slider(1, std::thread::hardware_concurrency(), this);

	void setup_parameters_layout() noexcept override;
	invoker_t create_invoker() const noexcept override;
};

}

#endif // INVOKE_CCFINDERX_DIALOG_HPP
