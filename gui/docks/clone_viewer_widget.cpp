#include "clone_viewer_widget.hpp"

namespace asterism
{

fragment_view::fragment_view(const clone_pair::fragment_order order, QWidget *parent) noexcept
	: QPlainTextEdit(parent), order_(order)
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

	auto block=this->firstVisibleBlock();
	int block_number=block.blockNumber();
	int top=int(this->blockBoundingGeometry(block).translated(this->contentOffset()).top());
	int bottom=top+int(this->blockBoundingRect(block).height());

	while(block.isValid() && top<=e->rect().bottom())
	{
		if(block.isVisible() && bottom>=e->rect().top())
		{
			auto number=QString::number(block_number+1);
			painter.setPen(Qt::darkBlue);
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

void fragment_view::change_file(const std::shared_ptr<file> &file, const shared_vector<clone_pair> &base) noexcept
{
	QFile ff(file->canonical_file_path());

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
	QTextStream in(&ff);
	in.setCodec("UTF-8");
	this->setPlainText(in.readAll());

	auto format=QTextBlockFormat();
	format.setBackground(QBrush(Qt::lightGray));

	this->base_first_blocks_.clear();

	if(base.empty())
	{
		return;
	}

	this->base_first_blocks_.resize(base.size());

	for(int i=0; i<base.size(); ++i)
	{
		int line_number=base[i]->fragment_of(this->order_).begin()-1;
		const int end=base[i]->fragment_of(this->order_).end()-1;
		auto block=this->document()->findBlockByLineNumber(line_number);
		this->base_first_blocks_[i].first=block;
		while(block.isValid() && line_number<=end)
		{
			QTextCursor(block).setBlockFormat(format);
			block=block.next();
			++line_number;
		}
		this->base_first_blocks_[i].second=block;
	}
}

void fragment_view::set_responses(const int index, const std::vector<response> &responses) noexcept
{
	if(responses.empty())
	{
		return;
	}

	this->scroll_to_base(index);
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

void fragment_view::scroll_to_base(const int index)
{
	this->setTextCursor(QTextCursor(this->base_first_blocks_[index].first));

	auto format=QTextBlockFormat();
	format.setBackground(QBrush(Qt::lightGray));
	for(auto b=this->base_first_blocks_[this->current_index_].first; b!=this->base_first_blocks_[this->current_index_].second; b=b.next())
	{
		QTextCursor(b).setBlockFormat(format);
	}

	format.setBackground(QBrush(QColor(193, 217, 255)));

	for(auto b=this->base_first_blocks_[index].first; b!=this->base_first_blocks_[index].second; b=b.next())
	{
		QTextCursor(b).setBlockFormat(format);
	}

	this->current_index_=index;
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

void clone_viewer_widget::change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const shared_vector<clone_pair> &base) noexcept
{
	this->f1_view_->change_file(file1, base);
	this->f2_view_->change_file(file2, base);
	this->setWindowTitle("Clone View");
}

void clone_viewer_widget::set_responses(const int index, const std::vector<response> &responses) noexcept
{
	this->f1_view_->set_responses(index, responses);
	this->f2_view_->set_responses(index, responses);
}

}