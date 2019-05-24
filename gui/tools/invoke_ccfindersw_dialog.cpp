#include "invoke_ccfindersw_dialog.hpp"

namespace asterism
{
void invoke_ccfindersw_dialog::setup_parameters_layout() noexcept
{
	this->len_->setMinimum(1);
	this->len_->setValue(50);
	this->detection_range_->addItem(tr("[0] All Clones"));
	this->detection_range_->addItem(tr("[1] Intra-file Clones"));
	this->detection_range_->addItem(tr("[2] Inter-file Clones"));
	this->b_antlr_->addButton(new QRadioButton(tr("Split codes by whitespaces")));
	this->b_antlr_->addButton(new QRadioButton(tr("Split codes by ANTLR")));
	this->charset_->set_languages({{"Shift-JIS", "sjis"}, {"UTF-8", "utf8"}, {"EUC-JP", "euc"}, {"Auto Detection", "auto"}});
	this->nolx_->setChecked(false);

	this->ccfsw_arg_->set_languages({{tr("Clone Pair"), "pair"}, {tr("Clone Set"), "set"}});
	this->json_indent_->set_languages({{tr("with indents"), "+"}, {tr("wittout indents"), "-"}});
	auto *ool=new QVBoxLayout;
	ool->addWidget(this->ccf_);
	ool->addWidget(this->ccfx_);
	auto *ccfswl=new QHBoxLayout;
	ccfswl->addWidget(this->ccfsw_);
	ccfswl->addWidget(this->ccfsw_arg_);
	ool->addLayout(ccfswl);
	auto *jl=new QHBoxLayout;
	jl->addWidget(this->json_);
	jl->addWidget(this->json_indent_);
	ool->addLayout(jl);
	this->output_options_->setLayout(ool);

	this->tks_->setMinimum(1);
	this->tks_->setValue(12);
	this->rnr_->setMinimum(0);
	this->rnr_->setMaximum(1);
	this->rnr_->setValue(0.3);
	this->rnr_->setSingleStep(0.1);
	auto *mfl=new QFormLayout;
	mfl->addRow(tr("Types of Tokens (-tks)"), this->tks_);
	mfl->addRow(tr("Ratio of non-repeated code (-rnr)"), this->rnr_);
	this->metrics_filtering_->setLayout(mfl);

}
}