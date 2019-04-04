#ifndef SCATTER_PLOT_VIEW_HPP
#define SCATTER_PLOT_VIEW_HPP

#include <QGraphicsView>
#include <QResizeEvent>

#include "core/logger.hpp"

namespace asterism
{


class scatter_plot_view final
	: public QGraphicsView
{
public:
	using QGraphicsView::QGraphicsView;

	virtual bool hasHeightForWidth() const override;
	virtual int heightForWidth(int w) const override;

protected:
	void resizeEvent(QResizeEvent *e) override;
};

}

#endif // SCATTER_PLOT_VIEW_HPP
