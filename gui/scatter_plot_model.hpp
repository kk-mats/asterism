#ifndef SCATTER_PLOT_MODEL_HPP
#define SCATTER_PLOT_MODEL_HPP

#include <QAbstractTableModel>
#include <QPainter>

#include "core/logger.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

class scatter_plot_model
	: public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit scatter_plot_model(QObject *parent=nullptr) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;

	void set_heatmap_layer(heatmap_layer &&heatmap_layer) noexcept;

private:
	heatmap_layer heatmap_layer_;
};

}
#endif // SCATTER_PLOT_MODEL_HPP
