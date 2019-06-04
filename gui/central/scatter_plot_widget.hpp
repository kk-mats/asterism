#ifndef SCATTER_PLOT_WIDGET_HPP
#define SCATTER_PLOT_WIDGET_HPP

#include <QHeaderView>
#include <QTableView>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPen>
#include <QPalette>
#include <QItemSelectionModel>
#include <QImage>

#include "core/logger.hpp"
#include "core/detection_results.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

class current_grid_delegate final
	: public QStyledItemDelegate
{
	Q_OBJECT

public:
	// inherits from QStyledItemDelegate
	using QStyledItemDelegate::QStyledItemDelegate;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept override;
};

class scatter_plot_model final
	: public QAbstractTableModel
{
	Q_OBJECT

public:
	// inherits from QAbstractTableModel
	using QAbstractTableModel::QAbstractTableModel;
	int rowCount(const QModelIndex &) const noexcept override;
	int columnCount(const QModelIndex &) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::BackgroundColorRole) const noexcept override;
	QVariant headerData(int, Qt::Orientation, int role=Qt::DisplayRole) const noexcept override;

	
	void set_layer(const std::shared_ptr<heatmap_layer> &layer, const QModelIndex &previous) noexcept;
	void change_method(const int method_index) noexcept;
	void update_layer();

	int grid_size_;
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
	void update_layer() noexcept;
	QImage export_current_scatter_plot() noexcept;

public slots:
	void select_grid(const QModelIndex &index) noexcept;
	void change_grid_size(const int size) noexcept;
	void change_method(const int method_index) noexcept;

signals:
	void current_grid_changed(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive);

private:
	const detection_results *results_;
	scatter_plot_model *model_=new scatter_plot_model(this);

	void set_grid_size(const int size=16) noexcept;
};

}

#endif // SCATTER_PLOT_WIDGET_HPP
