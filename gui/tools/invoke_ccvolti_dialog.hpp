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

class ccvolti_invoker final
{
public:
	ccvolti_invoker(const QString &dirname, const QString &lang, const QString &output, const double sim, const int size, const int sizeb, const int t) noexcept;
	void invoke(const QString &exe_path) noexcept;

private:
	QStringList args_;
};

class invoke_ccvolti_dialog final
	: public invoke_dialog
{
	Q_OBJECT

public:
	using invoke_dialog::invoke_dialog;
	using invoke_dialog::~invoke_dialog;

private:
	QSpinBox *size_=new QSpinBox(this);
	QSpinBox *sizeb_=new QSpinBox(this);
	QDoubleSpinBox *similarity_=new QDoubleSpinBox(this);
	threads_slider *threads_=new threads_slider(0, 1, this);

	void setup_parameters_layout() noexcept override;

	invoker_t create_invoker() const noexcept override;
};

}

#endif // INVOKE_CCVOLTI_DIALOG_HPP
