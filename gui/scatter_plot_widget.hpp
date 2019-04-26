#ifndef SCATTER_PLOT_WIDGET_HPP
#define SCATTER_PLOT_WIDGET_HPP

#include <QHeaderView>
#include <QTableView>
#include <QResizeEvent>
#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QItemSelectionModel>

#include "core/logger.hpp"
#include "core/detection_results.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

class scatter_plot_model final
	: public QAbstractTableModel
{
	Q_OBJECT

	friend class scatter_plot_widget;

public:
	explicit scatter_plot_model(QObject *parent=nullptr) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::BackgroundColorRole) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;

	QModelIndex previous_=QModelIndex();
	std::shared_ptr<heatmap_layer> current_layer_=nullptr;
};

class scatter_plot_widget final
	: public QTableView
{
	Q_OBJECT

public:
	explicit scatter_plot_widget(const detection_results *results, QWidget *parent=nullptr);

	void set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept;

public slots:
	void select_grid(const QModelIndex &index) noexcept;

signals:
	void current_grid_changed(const QString &filepath1, const QString &filepath2, const int clone_pair_size);

private:
	int grid_size=15;
	const detection_results *results_;
	scatter_plot_model *model_=new scatter_plot_model(this);
};

}

#endif // SCATTER_PLOT_WIDGET_HPP
