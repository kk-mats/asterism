#ifndef SCATTER_PLOT_MODEL_HPP
#define SCATTER_PLOT_MODEL_HPP

#include <QAbstractTableModel>
#include <QPainter>

#include "core/logger.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

class scatter_plot_model final
	: public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit scatter_plot_model(QObject *parent=nullptr) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;

	void set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept;

public slots:
	void select_grid(const QModelIndex &index) noexcept;

signals:
	void current_grid_changed(const QString &filepath1, const QString &filepath2, const int clone_pair_size);

private:
	std::shared_ptr<heatmap_layer> current_layer_=nullptr;
};

}
#endif // SCATTER_PLOT_MODEL_HPP
