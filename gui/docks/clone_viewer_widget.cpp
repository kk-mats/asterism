#include "clone_viewer_widget.hpp"

namespace asterism
{

fragment_view::fragment_view(QWidget *parent) noexcept
	: QPlainTextEdit(parent)
{
	this->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
	this->line_number_area_=new line_number_area(this);
	this->setReadOnly(true);

	connect(this, &fragment_view::blockCountChanged, this, &fragment_view::update_line_number_area_width);
	connect(this, &fragment_view::updateRequest, this, &fragment_view::update_linenumber_area);
	connect(this, &fragment_view::cursorPositionChanged, this, &fragment_view::highlight_current_line);

	this->update_line_number_area_width(0);
	this->highlight_current_line();
}

void fragment_view::line_number_area_paint_event(QPaintEvent *e) noexcept
{
	QPainter painter(this->line_number_area_);
	painter.fillRect(e->rect(), Qt::lightGray);

	auto block=this->firstVisibleBlock();
	int block_number=block.blockNumber();
	int top=int(this->blockBoundingGeometry(block).translated(this->contentOffset()).top());
	int bottom=top+int(this->blockBoundingRect(block).height());

	while(block.isValid() && top<=e->rect().bottom())
	{
		if(block.isVisible() && bottom>=e->rect().top())
		{
			auto number=QString::number(block_number+1);
			painter.setPen(Qt::black);
			painter.drawText(0, top, this->line_number_area_->width()-this->char_width(), this->fontMetrics().height(), Qt::AlignRight, number);
		}
		block=block.next();
		top=bottom;
		bottom=top+int(blockBoundingRect(block).height());
		++block_number;
	}
}

int fragment_view::line_number_area_width() noexcept
{
	int digits=3; // two for left margin and one for right margin
	int max=std::max(1, this->blockCount());
	while(max>=10)
	{
		max/=10;
		++digits;
	}

	int space=3+this->char_width()*digits;
	return space;
}

void fragment_view::change_file(const std::shared_ptr<file> &f, const clone_pair::fragment_order order) noexcept
{
	QFile ff(f->canonical_file_path());

	if(this->documentTitle()==ff.fileName())
	{
		return;
	}

	if(!ff.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qCritical()<<code_clone_loading_error::file_not_found<<ff.fileName();
		return;
	}

	this->setDocumentTitle(ff.fileName());
	this->setPlainText(QTextStream(&ff).readAll());
	this->order_=order;
}

void fragment_view::set_responses(const std::vector<response> &responses) noexcept
{
}

void fragment_view::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	auto cr=this->contentsRect();
	this->line_number_area_->setGeometry(QRect(cr.left(), cr.top(), this->line_number_area_width(), cr.height()));
}

void fragment_view::update_line_number_area_width(int) noexcept
{
	this->setViewportMargins(this->line_number_area_width(), 0, 0, 0);
}

void fragment_view::highlight_current_line() noexcept
{}

void fragment_view::update_linenumber_area(const QRect &rect, int dy) noexcept
{
	if(dy!=0)
	{
		this->line_number_area_->scroll(0, dy);
	}
	else
	{
		this->line_number_area_->update(0, rect.y(), this->line_number_area_->width(), rect.height());
	}

	if(rect.contains(this->viewport()->rect()))
	{
		this->update_line_number_area_width(0);
	}
}

int fragment_view::char_width() const noexcept
{
	return this->fontMetrics().horizontalAdvance(QLatin1Char('9'));
}


line_number_area::line_number_area(fragment_view *view) noexcept
	: QWidget(view), view_(view)
{}

QSize line_number_area::sizeHint() const
{
	return QSize(this->view_->line_number_area_width(), 0);
}

void line_number_area::paintEvent(QPaintEvent *e)
{
	this->view_->line_number_area_paint_event(e);
}


clone_viewer_widget::clone_viewer_widget(QWidget *parent) noexcept
	: QWidget(parent)
{
	auto *layout=new QHBoxLayout;
	layout->addWidget(this->f1_view_);
	layout->addWidget(this->f2_view_);
	this->setLayout(layout);
	this->setWindowFlag(Qt::Window);
	this->setAttribute(Qt::WA_QuitOnClose, false);
}

void clone_viewer_widget::change_current_grid(const std::shared_ptr<file> &f1, const std::shared_ptr<file> &f2) noexcept
{
	this->f1_view_->change_file(f1, clone_pair::fragment_order::first);
	this->f2_view_->change_file(f2, clone_pair::fragment_order::second);
	this->setWindowTitle("Clone View");
}

}