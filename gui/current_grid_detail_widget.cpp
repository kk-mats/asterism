#include "current_grid_detail_widget.hpp"

namespace asterism
{

current_grid_detail_widget::current_grid_detail_widget(QWidget *parent) noexcept
	: QWidget(parent)
{
	auto *filepath1_label=new QLabel(tr("Path: "), this);
	auto *filepath2_label=new QLabel(tr("Path: "), this);

	this->filepath1_->setPlaceholderText("no grid selected");
	this->filepath2_->setPlaceholderText("no grid selected");
	this->filepath1_->setReadOnly(true);
	this->filepath2_->setReadOnly(true);

	auto *filepath_layout=new QGridLayout(this);

	filepath_layout->addWidget(filepath1_label, 0, 0);
	filepath_layout->addWidget(filepath1_, 0, 1);
	filepath_layout->addWidget(filepath2_label, 1, 0);
	filepath_layout->addWidget(filepath2_, 1, 1);

	this->setLayout(filepath_layout);
}

void current_grid_detail_widget::change_current_grid(const QString &filepath1, const QString &filepath2, const int clone_pair_size) noexcept
{
	this->filepath1_->setText(filepath1);
	this->filepath2_->setText(filepath2);
}
}