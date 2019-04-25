#ifndef SCATTER_PLOT_VIEW_HPP
#define SCATTER_PLOT_VIEW_HPP

#include <QHeaderView>
#include <QTableView>
#include <QResizeEvent>
#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QPainter>

#include "core/logger.hpp"
#include "scatter_plot_model.hpp"

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

class scatter_plot_widget final
	: public QTableView
{
	Q_OBJECT

public:
	explicit scatter_plot_widget(QWidget *parent=nullptr);

public slots:
	void set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept;

private:
	scatter_plot_model *model_;
};

}

#endif // SCATTER_PLOT_VIEW_HPP
