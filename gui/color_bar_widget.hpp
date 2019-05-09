#pragma once

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QLinearGradient>
#include <QHBoxLayout>

#include "color_selector.hpp"

namespace asterism
{

class color_bar final
	: public QLabel
{
	Q_OBJECT

public:
	color_bar(QWidget *parent=nullptr) noexcept;
	
	void paintEvent(QPaintEvent *e) noexcept override;

	color_selector selector_;
};

class color_bar_widget final
	: public QWidget
{
	Q_OBJECT

public:
	color_bar_widget(QWidget *parent=nullptr) noexcept;
	~color_bar_widget();

	void set_selector(const color_selector &selector) noexcept;

private:
	QLabel *begin_=new QLabel(this);
	QLabel *end_=new QLabel(this);
	color_bar *color_bar_=new color_bar(this);
};

}
