#include "invoke_ccvolti_dialog.hpp"

namespace asterism
{

ccvolti_invoker::ccvolti_invoker(const QString &dirname, const QString &lang, const QString &output, const double sim, const int size, const int sizeb, const int t) noexcept
{
	const auto oc=output+".csv";
	const auto ocs=output+".txt";
	this->args_<<"-d"<<dirname<<"-l"<<lang<<"-oc"<<oc<<"-ocs"<<ocs<<"--sim"<<QString::number(sim)<<"--size"<<QString::number(size)<<"--sizeb"<<QString::number(sizeb)<<"-t"<<QString::number(t);
}

void ccvolti_invoker::invoke(const QString &exe_path) noexcept
{
	QProcess ccvolti;
	this->args_.push_front(exe_path);
	this->args_.push_front("-jar");
	ccvolti.setArguments(this->args_);
	ccvolti.start("java");
}


void invoke_ccvolti_dialog::setup_parameters_layout() noexcept
{
	this->language_->set_languages({{"Java", "java"}, {"C", "c"}, {"C#", "csharp"}});
	this->language_->setCurrentIndex(0);
	this->size_->setMinimum(1);
	this->size_->setValue(50);
	this->sizeb_->setMinimum(1);
	this->sizeb_->setValue(50);
	this->similarity_->setMinimum(0);
	this->similarity_->setMaximum(1);
	this->similarity_->setValue(0.9);
	this->similarity_->setSingleStep(0.1);

	auto *pl=new QFormLayout;
	pl->addRow(tr("Language (-l):"), this->language_);
	pl->addRow(tr("Method size (--size):"), this->size_);
	pl->addRow(tr("Block size (--sizeb):"), this->sizeb_);
	pl->addRow(tr("Similarity (--sim):"), this->similarity_);
	pl->addRow(tr("Threads (-t):"), this->threads_);
	this->parameters_layout_=pl;
}

invoke_dialog::invoker_t invoke_ccvolti_dialog::create_invoker() const noexcept
{
	return ccvolti_invoker(
		this->target_path_edit_->text(),
		this->language_->current_arg(),
		this->output_path_edit_->text(),
		this->similarity_->value(),
		this->size_->value(),
		this->sizeb_->value(),
		this->threads_->value()
	);
}
}