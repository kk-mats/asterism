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
	layout->addRow(tr("Path: "), this->filepath1_);
	layout->addRow(tr("Path: "), this->filepath2_);

	this->setLayout(layout);
}

void current_grid_detail_widget::change_current_grid(const QString &filepath1, const QString &filepath2, const int clone_pair_size) noexcept
{
	this->filepath1_->setText(filepath1);
	this->filepath2_->setText(filepath2);
}
}