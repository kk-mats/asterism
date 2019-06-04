#include "current_grid_detail_widget.hpp"

namespace asterism
{

current_grid_detail_widget::current_grid_detail_widget(QWidget *parent) noexcept
	: QWidget(parent)
{
	this->filepath1_->setPlaceholderText("no grid selected");
	this->filepath2_->setPlaceholderText("no grid selected");
	this->filepath1_->setReadOnly(true);
	this->filepath2_->setReadOnly(true);

	auto *layout=new QFormLayout;
	layout->addRow(tr("F1.Path: "), this->filepath1_);
	layout->addRow(tr("F2.Path: "), this->filepath2_);

	this->setLayout(layout);
}

void current_grid_detail_widget::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->filepath1_->setText(file1->canonical_file_path());
	this->filepath2_->setText(file2->canonical_file_path());
}
}