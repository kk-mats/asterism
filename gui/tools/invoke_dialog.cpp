#include "invoke_dialog.hpp"

namespace asterism
{
threads_slider::threads_slider(const int min, const int init, QWidget *parent) noexcept
	: QSlider(parent)
{
	const int n=std::thread::hardware_concurrency();
	const auto [n_min, n_max]=std::minmax(min, n>0 ? n : 1);
	this->setMinimum(n_min);
	this->setMaximum(n_max);
	this->setValue(std::clamp(n_min, init, n_max));
}


language_box::language_box(QWidget *parent) noexcept
	: QComboBox(parent)
{}

void language_box::set_languages(const std::vector<std::pair<QString, QString>> &param_arg) noexcept
{
	for(const auto &p:param_arg)
	{
		this->addItem(p.first+" ("+p.second+")", p.second);
	}
}

QString language_box::current_arg() const noexcept
{
	return this->currentData(Qt::UserRole).toString();
}


invoke_dialog::invoke_dialog(const QString &target, QWidget *parent) noexcept
	:QDialog(parent)
{
	this->target_path_edit_->setText(target);
	this->button_box_->button(QDialogButtonBox::Ok)->setText(tr("Start"));
	this->button_box_->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

	this->directory_layout_->addWidget(this->target_label_, 0, 0);
	this->directory_layout_->addWidget(this->target_path_edit_, 0, 1);
	this->directory_layout_->addWidget(this->target_browse_button_, 0, 2);
	this->directory_layout_->addWidget(this->output_label_, 1, 0);
	this->directory_layout_->addWidget(this->output_path_edit_, 1, 1);
	this->directory_layout_->addWidget(this->output_browse_button_, 1, 2);

	this->setup_parameters_layout();
	this->layout_->addLayout(this->directory_layout_);
	this->layout_->addLayout(this->parameters_layout_);
	this->layout->addWidget(this->button_box_);

	connect(this->target_browse_button_, &QPushButton::clicked, this, &invoke_dialog::get_target_path);
	connect(this->output_browse_button_, &QPushButton::clicked, this, &invoke_dialog::get_output_filename);
	connect(this->button_box_, &QDialogButtonBox::rejected, this, &QDialog::reject);
	connect(this->button_box_, &QDialogButtonBox::accepted, this, &invoke_dialog::dispatch_invoker);
	connect(this->button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);

	this->exec();
}

void invoke_dialog::get_target_path() noexcept
{
	if(const auto path=QFileDialog::getExistingDirectory(this, tr("Select your target project")); !path.isEmpty())
	{
		this->target_path_edit_->setText(path);
	}
}

void invoke_dialog::get_output_filename() noexcept
{
	if(const auto path=QFileDialog::getSaveFileName(this, tr("Save code clone detection result")); !path.isEmpty())
	{
		this->output_path_edit_->setText(path);
	}
}

void invoke_dialog::dispatch_invoker() noexcept
{
	emit invoker_dispatched(this->create_invoker());
}

}