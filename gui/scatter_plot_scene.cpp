#include "scatter_plot_scene.hpp"

namespace asterism
{

scatter_plot_scene::scatter_plot_scene(QObject *parent)
	: QGraphicsScene(parent), min_grid_size_(10), n_grid_(10)
{
}


void scatter_plot_scene::drawBackground(QPainter *painter, const QRectF &rect)
{
	auto r=rect.toRect();
	QColor border_color(0, 0, 0);
	painter->setPen(border_color);

	const auto left=r.left(), top=r.top();
	const auto grid_size=std::max(std::min(r.width(), r.height())/this->n_grid_, this->min_grid_size_);

	const auto plot_size=grid_size*this->n_grid_;
	const auto plot_bottom=top+plot_size;
	const auto plot_right=left+plot_size;

	for(auto c=left; c<plot_size; c+=grid_size)
	{
		painter->drawLine(c, top, c, plot_bottom);
	}

	for(auto c=top; c<plot_size; c+=grid_size)
	{
		painter->drawLine(left, c, plot_right, c);
	}
}

}
