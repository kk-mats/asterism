#ifndef INVOKE_CCFINDERSW_DIALOG_HPP
#define INVOKE_CCFINDERSW_DIALOG_HPP

#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QFormLayout>

#include "invoke_dialog.hpp"

namespace asterism
{

class ccfindersw_invoker final
{

};

class invoke_ccfindersw_dialog final
	: public invoke_dialog
{
	Q_OBJECT

public:
	using invoke_dialog::invoke_dialog;
	using invoke_dialog::~invoke_dialog;

private:
	QLineEdit *language_edit_=new QLineEdit(this);
	QSpinBox *len_=new QSpinBox(this);
	QComboBox *detection_range_=new QComboBox(this);
	QButtonGroup *b_antlr_=new QButtonGroup(this);
	language_box *charset_=new language_box(this);
	QCheckBox *nolx_=new QCheckBox(this);

	QGroupBox *output_options_=new QGroupBox(tr("Output options"), this);
	QCheckBox *ccf_=new QCheckBox(tr("Output in CCFinder format"),this);
	QCheckBox *ccfx_=new QCheckBox(tr("Output in CCFinderX format"), this);
	QCheckBox *ccfsw_=new QCheckBox(tr("Output in CCFinderSW format"), this);
	language_box *ccfsw_arg_=new language_box(this);
	QCheckBox *json_=new QCheckBox(tr("Output in JSON format"), this);
	language_box *json_indent_=new language_box(this);

	QGroupBox *metrics_filtering_=new QGroupBox(tr("Metrics filtering"), this);
	QSpinBox *tks_=new QSpinBox(this);
	QDoubleSpinBox *rnr_=new QDoubleSpinBox(this);

	void setup_parameters_layout() noexcept override;
	invoker_t create_invoker() const noexcept override;
};

}

#endif // INVOKE_CCFINDERSW_DIALOG_HPP
