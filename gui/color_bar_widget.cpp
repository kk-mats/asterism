#include "color_bar_widget.hpp"

namespace asterism
{

color_bar::color_bar(QWidget *parent, const color_selector &selector, const int factor) noexcept
	: selector_(selector), QLabel(parent)
{
	this->setFixedWidth(this->height()*factor);
}

void color_bar::paintEvent(QPaintEvent *e) noexcept
{
	QPainter painter(this);
	painter.setPen(QPen(Qt::gray, 1));

	float len=this->selector_.last()-this->selector_.first();
	int low=this->selector_.first();
	QLinearGradient grad(e->rect().topLeft(), e->rect().topRight());
	for(const auto &c:this->selector_)
	{
		grad.setColorAt((c.first-low)/len, c.second);
	}
	painter.setBrush(grad);
	painter.drawRect(e->rect());
}

color_bar_widget::color_bar_widget(QWidget *parent) noexcept
	: QWidget(parent)
{
	this->mismatch0_->setText("0");
	this->mismatch0_->setVisible(false);
	this->mismatch0_bar_->setVisible(false);

	auto *layout=new QHBoxLayout;
	layout->addWidget(this->mismatch0_);
	layout->addWidget(this->mismatch0_bar_);
	layout->addWidget(this->begin_);
	layout->addWidget(this->color_bar_);
	layout->addWidget(this->end_);
	this->setLayout(layout);
}

color_bar_widget::color_bar_widget(const color_selector &selector, QWidget *parent) noexcept
	: color_bar_widget(parent)
{}

color_bar_widget::~color_bar_widget()
{
}

void color_bar_widget::set_selector(const color_selector &selector, const int method_index) noexcept
{

	this->mismatch0_->setVisible(method_index==1);
	this->mismatch0_bar_->setVisible(method_index==1);
	this->begin_->setText(QString::number(selector.first()));
	this->end_->setText(QString::number(selector.last())+(method_index==1 ? "%" : " Clone Pair(s)"));
	this->color_bar_->selector_=selector;
	this->color_bar_->repaint();
}


}