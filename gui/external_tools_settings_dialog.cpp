#include "external_tools_settings_dialog.hpp"

namespace asterism
{

clone_detector_page::clone_detector_page(const QString &init, QWidget *parent) noexcept
	: QDialog(parent), init(init)
{
	this->path_label_=new QLabel(tr("Path: "));
	this->path_line_=new QLineEdit(this->init);
	this->browse_button_=new QPushButton(tr("Browse"));
	this->browse_button_->setAutoDefault(false);
	this->browse_button_->setDefault(false);

	this->path_layout_=new QHBoxLayout;
	this->path_layout_->addWidget(this->path_label_);
	this->path_layout_->addWidget(this->path_line_);
	this->path_layout_->addWidget(this->browse_button_);

	connect(this->browse_button_, &QPushButton::clicked, this, &clone_detector_page::set_path);
}

void clone_detector_page::set_path() noexcept
{
	if(const auto path=QFileDialog::getOpenFileName(this, "Path to "+init); !path.isEmpty())
	{
		this->path_line_->setText(path);
	}
}

nicad_page::nicad_page(QWidget *parent) noexcept
	: clone_detector_page("nicad5", parent)
{
	this->setLayout(this->path_layout_);
}

ccfx_page::ccfx_page(QWidget *parent) noexcept
	: clone_detector_page("ccfx.exe", parent)
{
	this->setLayout(this->path_layout_);
}

ccvolti_page::ccvolti_page(QWidget *parent) noexcept
	: clone_detector_page("ccvolti.jar", parent)
{
	this->setLayout(this->path_layout_);
}

ccsw_page::ccsw_page(QWidget *parent) noexcept
	: clone_detector_page("ccfx.exe", parent)
{
	this->setLayout(this->path_layout_);
}


external_tools_settings_dialog::external_tools_settings_dialog(QWidget *parent) noexcept
	: QDialog(parent)
{
	auto *ccfx=new QListWidgetItem(this->tools_list_widget_);
	ccfx->setText(clone_detector::ccfinderx.name());

	auto *nicad=new QListWidgetItem(this->tools_list_widget_);
	nicad->setText(clone_detector::nicad.name());

	auto *ccvolti=new QListWidgetItem(this->tools_list_widget_);
	ccvolti->setText(clone_detector::ccvolti.name());

	auto *ccsw=new QListWidgetItem(this->tools_list_widget_);
	ccsw->setText(clone_detector::ccfindersw.name());


	this->content_widget_->addWidget(new ccfx_page);
	this->content_widget_->addWidget(new nicad_page);
	this->content_widget_->addWidget(new ccvolti_page);
	this->content_widget_->addWidget(new ccsw_page);

	auto *layout=new QHBoxLayout;
	layout->addWidget(this->tools_list_widget_);
	layout->addWidget(this->content_widget_);
	layout->setStretch(0, 2);
	layout->setStretch(1, 5);
	this->setLayout(layout);

	connect(this->tools_list_widget_, &QListWidget::currentItemChanged, this, &external_tools_settings_dialog::change_page);
	this->exec();
}

external_tools_settings_dialog::~external_tools_settings_dialog()
{
}

void external_tools_settings_dialog::change_page(QListWidgetItem *current, QListWidgetItem *previous) noexcept
{
	if(!current)
	{
		current=previous;
	}

	this->content_widget_->setCurrentIndex(this->tools_list_widget_->row(current));
}
}