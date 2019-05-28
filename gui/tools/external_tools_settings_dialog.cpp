#include "external_tools_settings_dialog.hpp"

namespace asterism
{

clone_detector_page::clone_detector_page(const QString &tool_name, QWidget *parent) noexcept
	: QDialog(parent), tool_name_(tool_name)
{
	this->path_label_=new QLabel(tr("Path: "));
	this->path_line_=new QLineEdit(global_settings::instance().value({global_settings::EXTERNAL_TOOLS, this->tool_name_, global_settings::EXECUTABLE_PATH}));
	this->path_line_->home(true);

	this->browse_button_=new QPushButton(tr("Browse"));
	this->browse_button_->setAutoDefault(false);
	this->browse_button_->setDefault(false);

	this->path_layout_=new QHBoxLayout;
	this->path_layout_->addWidget(this->path_label_);
	this->path_layout_->addWidget(this->path_line_);
	this->path_layout_->addWidget(this->browse_button_);

	connect(this->browse_button_, &QPushButton::clicked, this, &clone_detector_page::set_path);
}

void clone_detector_page::save() noexcept
{
	global_settings::instance().set(this->path_text(), {global_settings::EXTERNAL_TOOLS, this->tool_name_, global_settings::EXECUTABLE_PATH});
}

QString clone_detector_page::path_text() const noexcept
{
	return this->path_line_->text();
}

void clone_detector_page::set_path() noexcept
{
	if(const auto path=QFileDialog::getOpenFileName(this, "Executable path to "+this->tool_name_, this->path_line_->text()); !path.isEmpty())
	{
		this->path_line_->setText(path);
	}
}

nicad_page::nicad_page(QWidget *parent) noexcept
	: clone_detector_page(clone_detector::nicad.name(), parent)
{
	
	this->setLayout(this->path_layout_);
}

ccfinderx_page::ccfinderx_page(QWidget *parent) noexcept
	: clone_detector_page(clone_detector::ccfinderx.name(), parent)
{
	this->setLayout(this->path_layout_);
}

ccvolti_page::ccvolti_page(QWidget *parent) noexcept
	: clone_detector_page(clone_detector::ccvolti.name(), parent)
{
	this->setLayout(this->path_layout_);
}

ccfindersw_page::ccfindersw_page(QWidget *parent) noexcept
	: clone_detector_page(clone_detector::ccfindersw.name(), parent)
{
	this->setLayout(this->path_layout_);
}


external_tools_settings_dialog::external_tools_settings_dialog(QWidget *parent) noexcept
	: QDialog(parent)
{
	auto *ccfinderx=new QListWidgetItem(this->tools_list_widget_);
	ccfinderx->setText(clone_detector::ccfinderx.name());

	auto *nicad=new QListWidgetItem(this->tools_list_widget_);
	nicad->setText(clone_detector::nicad.name());

	auto *ccvolti=new QListWidgetItem(this->tools_list_widget_);
	ccvolti->setText(clone_detector::ccvolti.name());

	auto *ccfindersw=new QListWidgetItem(this->tools_list_widget_);
	ccfindersw->setText(clone_detector::ccfindersw.name());


	this->content_widget_->addWidget(new ccfinderx_page);
	this->content_widget_->addWidget(new nicad_page);
	this->content_widget_->addWidget(new ccvolti_page);
	this->content_widget_->addWidget(new ccfindersw_page);

	this->tools_list_widget_->setCurrentRow(0);
	this->content_widget_->setCurrentIndex(0);

	auto *body_layout=new QHBoxLayout;
	body_layout->addWidget(this->tools_list_widget_);
	body_layout->addWidget(this->content_widget_);
	body_layout->setStretch(0, 2);
	body_layout->setStretch(1, 5);

	auto *layout=new QVBoxLayout;
	layout->addLayout(body_layout);
	layout->addWidget(this->button_box_);
	this->setLayout(layout);
	
	connect(this->tools_list_widget_, &QListWidget::currentItemChanged, this, &external_tools_settings_dialog::change_page);
	connect(this->button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(this->button_box_, &QDialogButtonBox::rejected, this, &external_tools_settings_dialog::reject);
}

external_tools_settings_dialog::~external_tools_settings_dialog()
{
}

void external_tools_settings_dialog::accept() noexcept
{
	for(int i=0; i<this->content_widget_->count(); ++i)
	{
		static_cast<clone_detector_page *>(this->content_widget_->widget(i))->save();
	}
	global_settings::instance().sync();
	this->close();
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