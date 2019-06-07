#include "invoke_nicad_dialog.hpp"

namespace asterism
{

invoke_nicad_dialog::invoke_nicad_dialog(const QString &target, QWidget *parent) noexcept
	: invoke_dialog(target, parent)
{
	this->setWindowTitle(tr("NiCAD"));
	this->begin_setup_parameters_layout();
	this->end_setup_parameters_layout();
}

void invoke_nicad_dialog::begin_setup_parameters_layout() noexcept
{
	this->granularity_->addItems({"blocks", "functions"});

	this->language_=new key_arg_box(this);
	this->language_->set_values({{"C", "c"}, {"C#", "cs"}, {"Java", "java"}, {"Python", "py"}});

	auto *pl=new QFormLayout;
	pl->addRow(tr("Granularity:"), this->granularity_);
	pl->addRow(tr("Language"), this->language_);
	this->parameters_layout_=pl;
}

invoker_t invoke_nicad_dialog::create_invoker() const noexcept
{
	return nicad_invoker();
}
}