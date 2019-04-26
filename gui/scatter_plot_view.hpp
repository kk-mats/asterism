#ifndef SCATTER_PLOT_VIEW_HPP
#define SCATTER_PLOT_VIEW_HPP

#include <QHeaderView>
#include <QTableView>
#include <QResizeEvent>
#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QPainter>

#include "core/logger.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

static constexpr int grid_size=15;

class scatter_plot_delegate
	: public QAbstractItemDelegate
{
	Q_OBJECT

public:
	using QAbstractItemDelegate::QAbstractItemDelegate;

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize scatter_plot_delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

class scatter_plot_view final
	: public QTableView
{
	Q_OBJECT

public:
	explicit scatter_plot_view(QWidget *parent=nullptr);
};

}

#endif // SCATTER_PLOT_VIEW_HPP
