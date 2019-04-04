#ifndef SCATTER_PLOT_SCENE_HPP
#define SCATTER_PLOT_SCENE_HPP

#include <QGraphicsScene>
#include <QPainter>

#include "core/logger.hpp"

namespace asterism
{

class scatter_plot_scene final
		: public QGraphicsScene
{
	Q_OBJECT

public:
	explicit scatter_plot_scene(QObject *parent=nullptr);

protected:
	virtual void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
	int min_grid_size_;
	int n_grid_;
};

}
#endif // SCATTER_PLOT_SCENE_HPP
