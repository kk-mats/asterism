#include "scatter_plot_view.hpp"

namespace asterism
{

bool scatter_plot_view::hasHeightForWidth() const
{
	return true;
}

int scatter_plot_view::heightForWidth(int w) const
{
	return w;
}

void scatter_plot_view::resizeEvent(QResizeEvent *e)
{
	e->accept();
	const auto size=std::min(this->size().height(), this->size().width());
	this->resize(size, size);
}

}
