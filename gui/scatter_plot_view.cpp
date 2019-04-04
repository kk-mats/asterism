#include "scatter_plot_view.hpp"

namespace asterism
{

bool scatter_plot_view::hasHeightForWidth() const
{
	return true;
}

int scatter_plot_view::heightForWidth(int w) const
{
	qDebug()<<"Called";
	return w;
}

void scatter_plot_view::resizeEvent(QResizeEvent *e)
{

}

}
