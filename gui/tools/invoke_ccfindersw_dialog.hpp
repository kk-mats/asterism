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

class invoke_ccfindersw_dialog final
	: public invoke_dialog
{
	Q_OBJECT

public:
	invoke_ccfindersw_dialog(const QString &target, QWidget *parent) noexcept;
	invoker_t create_invoker() const noexcept override;

private:
	QLineEdit *language_edit_=new QLineEdit(this);
	QSpinBox *len_=new QSpinBox(this);
	QComboBox *detection_range_=new QComboBox(this);
	QRadioButton *b_=new QRadioButton(tr("Split codes by whitespaces"), this);
	QRadioButton *antlr_=new QRadioButton(tr("Split codes by ANTLR"), this);
	QButtonGroup *b_antlr_=new QButtonGroup(this);
	QGroupBox *splitting_method_=new QGroupBox(tr("Splitting method"), this);
	key_arg_box *charset_=new key_arg_box(this);
	QCheckBox *nolx_=new QCheckBox(tr("Use lexical analysis cache"), this);

	QGroupBox *output_options_=new QGroupBox(tr("Output options"), this);
	QCheckBox *ccf_=new QCheckBox(tr("Output in CCFinder format"),this);
	QCheckBox *ccfx_=new QCheckBox(tr("Output in CCFinderX format"), this);
	QCheckBox *ccfsw_=new QCheckBox(tr("Output in CCFinderSW format"), this);
	key_arg_box *ccfsw_arg_=new key_arg_box(this);
	QCheckBox *json_=new QCheckBox(tr("Output in JSON format"), this);
	key_arg_box *json_indent_=new key_arg_box(this);

	QGroupBox *metrics_filtering_=new QGroupBox(tr("Metrics filtering"), this);
	QSpinBox *tks_=new QSpinBox(this);
	QDoubleSpinBox *rnr_=new QDoubleSpinBox(this);

	void begin_setup_parameters_layout() noexcept override;
};

}

#endif // INVOKE_CCFINDERSW_DIALOG_HPP
