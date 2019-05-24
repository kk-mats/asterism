#ifndef COLOR_BAR_WIDGET_HPP
#define COLOR_BAR_WIDGET_HPP

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QLinearGradient>
#include <QHBoxLayout>

#include "layer/color_selector.hpp"

namespace asterism
{

class color_bar final
	: public QLabel
{
	Q_OBJECT

public:
	color_bar(QWidget *parent=nullptr, const color_selector &selector=color_selector(), const int factor=6) noexcept;
	
	void paintEvent(QPaintEvent *e) noexcept override;

	color_selector selector_;
};

class color_bar_widget final
	: public QWidget
{
	Q_OBJECT

public:
	color_bar_widget(QWidget *parent=nullptr) noexcept;
	color_bar_widget(const color_selector &selector, QWidget *parent=nullptr) noexcept;
	~color_bar_widget();

	void set_selector(const color_selector &selector, const int method_index) noexcept;

private:
	QLabel *begin_=new QLabel(this);
	QLabel *end_=new QLabel(this);
	color_bar *color_bar_=new color_bar(this);

	QLabel *mismatch0_=new QLabel(this);
	color_bar *mismatch0_bar_=new color_bar(this, color_selector({{0, QColor(0xb4, 0xff, 0x70)}, {1, QColor(0xb4, 0xff, 0x70)}}), 1);
};

}

#endif // COLOR_BAR_WIDGET_HPP