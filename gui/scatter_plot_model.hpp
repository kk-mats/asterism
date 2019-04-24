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

	void add_heatmap_layers(QList<heatmap_layer> &&layers) noexcept;
	void add_heatmap_layer(heatmap_layer &&layer) noexcept;
	bool update() noexcept;

	const std::shared_ptr<QList<heatmap_layer>> &layers() const noexcept;

public slots:
	void change_current_layer(const QModelIndex &index) noexcept;

private:
	int current_index_=0;
	heatmap_layer *current_layer_=nullptr;
	std::shared_ptr<QList<heatmap_layer>> layers_=std::make_shared<QList<heatmap_layer>>();
};

}
#endif // SCATTER_PLOT_MODEL_HPP
