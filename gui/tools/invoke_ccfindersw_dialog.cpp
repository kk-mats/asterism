#include "invoke_ccfindersw_dialog.hpp"

namespace asterism
{

invoke_ccfindersw_dialog::invoke_ccfindersw_dialog(const QString &target, QWidget *parent) noexcept
	: invoke_dialog(target, parent)
{
	this->setWindowTitle(tr("CCFidnerSW"));
	this->begin_setup_parameters_layout();
	this->end_setup_parameters_layout();
}

void invoke_ccfindersw_dialog::begin_setup_parameters_layout() noexcept
{
	this->len_->setMinimum(1);
	this->len_->setValue(50);
	this->detection_range_->addItem(tr("[0] All Clones"));
	this->detection_range_->addItem(tr("[1] Intra-file Clones"));
	this->detection_range_->addItem(tr("[2] Inter-file Clones"));
	this->b_antlr_->addButton(this->b_);
	this->b_antlr_->addButton(this->antlr_);
	this->b_antlr_->setExclusive(true);
	this->charset_->set_values({{"Shift-JIS", "sjis"}, {"UTF-8", "utf8"}, {"EUC-JP", "euc"}, {"Auto Detection", "auto"}});
	this->nolx_->setChecked(false);
	auto *dl=new QFormLayout;
	dl->addRow(tr("Language (-l):"), this->language_edit_);
	dl->addRow(tr("Clone length (-t):"), this->len_);
	dl->addRow(tr("Detetion range (-w):"), this->detection_range_);
	dl->addRow(tr("Encode (-charset):"), this->charset_);
	auto *b_antlr=new QVBoxLayout;
	b_antlr->addWidget(this->b_);
	b_antlr->addWidget(this->antlr_);
	this->splitting_method_->setLayout(b_antlr);
	dl->addRow(this->splitting_method_);
	dl->addRow(this->nolx_);
	
	this->ccfsw_arg_->set_values({{tr("Clone Pair"), "pair"}, {tr("Clone Set"), "set"}});
	this->json_indent_->set_values({{tr("with indents"), "+"}, {tr("wittout indents"), "-"}});
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
	dl->addRow(this->output_options_);

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

	dl->addRow(this->metrics_filtering_);
	this->parameters_layout_=dl;
}

invoke_dialog::invoker_t invoke_ccfindersw_dialog::create_invoker() const noexcept
{
	return ccfindersw_invoker();
}
}