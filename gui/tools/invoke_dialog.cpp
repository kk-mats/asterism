#include "invoke_dialog.hpp"

namespace asterism
{
threads_selector::threads_selector(const int min, const int init, QWidget *parent) noexcept
	: QWidget(parent)
{
	const int n=std::thread::hardware_concurrency();
	const auto [n_min, n_max]=std::minmax(min, n>0 ? n : 1);
	this->slider_->setMinimum(n_min);
	this->spinbox_->setMinimum(n_min);
	this->slider_->setMaximum(n_max);
	this->spinbox_->setMaximum(n_max);
	this->slider_->setValue(std::clamp(n_min, init, n_max));
	this->spinbox_->setValue(std::clamp(n_min, init, n_max));

	auto *layout=new QHBoxLayout(this);
	layout->addWidget(this->slider_);
	layout->addWidget(this->spinbox_);
	this->setLayout(layout);

	connect(this->slider_, &QSlider::valueChanged, this, &threads_selector::slider_value_changed);
	connect(this->spinbox_, qOverload<int>(&QSpinBox::valueChanged), this, &threads_selector::spinbox_value_changed);
}

void threads_selector::slider_value_changed(const int i) noexcept
{
	if(this->spinbox_->value()!=i)
	{
		this->spinbox_->setValue(i);
	}
}

void threads_selector::spinbox_value_changed(const int i) noexcept
{
	if(this->slider_->value()!=i)
	{
		this->slider_->setValue(i);
	}
}

int threads_selector::value() const noexcept
{
	return this->slider_->value();
}

key_arg_box::key_arg_box(QWidget *parent) noexcept
	: QComboBox(parent)
{}

void key_arg_box::set_values(const std::vector<std::pair<QString, QString>> &values) noexcept
{
	for(const auto &p:values)
	{
		this->addItem(p.first+" ["+p.second+"]", p.second);
	}
}

QString key_arg_box::current_arg() const noexcept
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

	connect(this->target_browse_button_, &QPushButton::clicked, this, &invoke_dialog::get_target_path);
	connect(this->output_browse_button_, &QPushButton::clicked, this, &invoke_dialog::get_output_filename);
	connect(this->button_box_, &QDialogButtonBox::rejected, this, &QDialog::reject);
	connect(this->button_box_, &QDialogButtonBox::accepted, this, &invoke_dialog::dispatch_invoker);
	connect(this->button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
}

invoke_dialog::~invoke_dialog() noexcept
{
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

void invoke_dialog::end_setup_parameters_layout() noexcept
{
	this->layout_->addLayout(this->parameters_layout_);
	this->layout_->addSpacing(1);
	this->layout_->addLayout(this->directory_layout_);
	this->layout_->addWidget(this->button_box_);
	this->setLayout(this->layout_);
}


}