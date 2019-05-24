#include "invoke_ccfinderx_dialog.hpp"

namespace asterism
{

invoke_ccfinderx_dialog::invoke_ccfinderx_dialog(const QString &target, QWidget *parent) noexcept
	: invoke_dialog(target, parent)
{
	this->setWindowTitle(tr("CCFidnerX"));
	this->begin_setup_parameters_layout();
	this->end_setup_parameters_layout();
}

void invoke_ccfinderx_dialog::begin_setup_parameters_layout() noexcept
{
	this->language_=new key_arg_box(this);
	this->language_->set_values({
		{"Cobol", "cobol"}, {"C/C++", "cpp"}, {"C#", "csharp"},
		{"Java", "java"}, {"Visual Basic", "visualbasic"}, {"Plain Text", "plaintext"}
	});
	this->len_->setMinimum(1);
	this->len_->setValue(50);
	this->tks_->setMinimum(1);
	this->len_->setValue(12);
	this->intra_file_clones_->setChecked(true);
	this->inter_file_clones_->setChecked(true);

	auto *pl=new QFormLayout;
	pl->addRow(tr("Language:"), this->language_);
	pl->addRow(tr("Clone length (-b):"), this->len_);
	pl->addRow(tr("Types of tokens (-t):"), this->tks_);
	pl->addRow(tr("Threads (--threads):"), this->threads_);
	pl->addRow(this->inter_file_clones_);
	pl->addRow(this->intra_file_clones_);
	this->parameters_layout_=pl;
}

invoke_dialog::invoker_t invoke_ccfinderx_dialog::create_invoker() const noexcept
{
	return ccfinderx_invoker(
		this->target_path_edit_->text(),
		this->output_path_edit_->text(),
		this->language_->current_arg(),
		this->len_->value(),
		this->tks_->value(),
		this->inter_file_clones_->isChecked(),
		this->intra_file_clones_->isChecked(),
		this->threads_->value()
	);
}
}