#include "invoke_clone_detector_dialog.hpp"

namespace asterism
{

ccvolti_invoker::ccvolti_invoker(const QString &dirname, const QString &lang, const QString & output, const double sim, const int size, const int sizeb, const int t) noexcept
{
	this->args_<<"-d"<<dirname<<"-l"<<lang<<"--sim"<<QString::number(sim)<<"--size"<<QString::number(size)<<"--sizeb"<<QString::number(sizeb)<<"-t"<<QString::number(t);
}


void ccvolti_invoker::invoke(const QString &exe_path) noexcept
{
	QProcess ccvolti;
	this->args_.push_front(exe_path);
	this->args_.push_front("-jar");
	ccvolti.setArguments(this->args_);
	ccvolti.start("java");
}

invoke_ccvolti_dialog::invoke_ccvolti_dialog(const QString &target, QWidget *parent)
	: QDialog(parent)
{
	this->target_path_edit_->setText(target);
	
	this->language_box_->addItem("Java (java)");
	this->language_box_->addItem("C (c)");
	this->language_box_->addItem("C# (charp)");
	this->language_box_->setCurrentIndex(0);
	this->size_box_->setMinimum(0);
	this->size_box_->setValue(50);
	this->sizeb_box_->setMinimum(0);
	this->sizeb_box_->setValue(50);
	this->similarity_box_->setMinimum(0);
	this->similarity_box_->setMaximum(1);
	this->similarity_box_->setValue(0.9);
	this->threads_box_->setMinimum(0);
	this->threads_box_->setMaximum(std::thread::hardware_concurrency());
	this->threads_box_->setValue(1);

	auto *directory_layout=new QGridLayout;
	directory_layout->addWidget(this->target_label_, 0, 0);
	directory_layout->addWidget(this->target_path_edit_, 0, 1);
	directory_layout->addWidget(this->target_browse_button_, 0, 2);

	directory_layout->addWidget(this->output_label_, 1, 0);
	directory_layout->addWidget(this->output_path_edit_, 1, 1);
	directory_layout->addWidget(this->output_browse_button_, 1, 2);

	auto *parameters_layout=new QFormLayout;
	parameters_layout->addRow(tr("Language (-l):"), this->language_box_);
	parameters_layout->addRow(tr("Method size (--size):"), this->size_box_);
	parameters_layout->addRow(tr("Block size (--sizeb):"), this->sizeb_box_);
	parameters_layout->addRow(tr("Similarity (--sim):"), this->similarity_box_);
	parameters_layout->addRow(tr("Threads (-t):"), this->threads_box_);

	auto *button_box=new QDialogButtonBox(
		QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal
	);
	button_box->button(QDialogButtonBox::Ok)->setText(tr("Start"));
	button_box->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

	auto *layout=new QVBoxLayout;
	layout->addLayout(directory_layout);
	layout->addLayout(parameters_layout);
	layout->addWidget(button_box);
	this->setLayout(layout);

	connect(this->target_browse_button_, &QPushButton::clicked, this, &invoke_ccvolti_dialog::get_target_path);
	connect(this->output_browse_button_, &QPushButton::clicked, this, &invoke_ccvolti_dialog::get_output_filename);
	connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
	connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);

	this->exec();
}

invoke_ccvolti_dialog::~invoke_ccvolti_dialog()
{
}

void invoke_ccvolti_dialog::get_target_path() noexcept
{
	if(const auto path=QFileDialog::getExistingDirectory(this, tr("Clone Detection Target Directory")); !path.isEmpty())
	{
		this->target_path_edit_->setText(path);
	}
}

void invoke_ccvolti_dialog::get_output_filename() noexcept
{
	if(const auto path=QFileDialog::getSaveFileName(this, tr("Save code clone detection result")); !path.isEmpty())
	{
		this->output_path_edit_->setText(path);
	}
}

}