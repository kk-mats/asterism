#ifndef CLONE_VIEWER_WIDGET_HPP
#define CLONE_VIEWER_WIDGET_HPP

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QTextStream>
#include <QFile>
#include <QDialog>
#include <QFontDatabase>
#include <QBoxLayout>

#include "core/matching_table.hpp"


namespace asterism
{

class fragment_view final
	: public QPlainTextEdit
{
	Q_OBJECT
public:
	explicit fragment_view(QWidget *parent=nullptr) noexcept;

	void line_number_area_paint_event(QPaintEvent *e) noexcept;
	int line_number_area_width() noexcept;

	void change_file(const std::shared_ptr<file> &f, const clone_pair::fragment_order order) noexcept;
	void set_responses(const std::vector<response> &responses) noexcept;

protected:
	void resizeEvent(QResizeEvent *e) override;

private slots:
	void update_line_number_area_width(int) noexcept;
	void highlight_current_line() noexcept;
	void update_linenumber_area(const QRect &rect, int dy) noexcept;

private:
	QWidget *line_number_area_;
	clone_pair::fragment_order order_;

	int char_width() const noexcept;
};


class line_number_area final
	: public QWidget
{
	Q_OBJECT
public:
	explicit line_number_area(fragment_view *view) noexcept;

	QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent *e) override;

private:
	fragment_view *view_;
};


class clone_viewer_widget final
	: public QWidget
{
	Q_OBJECT
public:
	explicit clone_viewer_widget(QWidget *parent=nullptr) noexcept;
	void destroy();

public slots:
	void change_current_grid(const std::shared_ptr<file> &f1, const std::shared_ptr<file> &f2) noexcept;

private:
	fragment_view *f1_view_=new fragment_view(this);
	fragment_view *f2_view_=new fragment_view(this);
};


}


#endif // CLONE_VIEWER_WIDGET_HPP
