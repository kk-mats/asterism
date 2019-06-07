#ifndef INVOKE_NICAD_DIALOG_HPP
#define INVOKE_NICAD_DIALOG_HPP

#include <QFormLayout>

#include "invoke_dialog.hpp"

namespace asterism
{

class invoke_nicad_dialog final
	: public invoke_dialog
{
	Q_OBJECT

public:
	invoke_nicad_dialog(const QString &target, QWidget *parent) noexcept;
	invoker_t create_invoker() const noexcept override;

private:
	QComboBox *granularity_=new QComboBox(this);

	void begin_setup_parameters_layout() noexcept override;
};

}

#endif // INVOKE_NICAD_DIALOG_HPP
