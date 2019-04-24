#ifndef LAYER_LIST_MODEL_HPP
#define LAYER_LIST_MODEL_HPP

#include <QAbstractListModel>
#include <list>

#include "layer/heatmap_layer.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class layer_list_model
	: public QAbstractListModel
{
	Q_OBJECT

public:
	explicit layer_list_model(const std::shared_ptr<const QList<heatmap_layer>> &layers, QObject *parent=nullptr) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;

public slots:


private:
	const std::shared_ptr<const QList<heatmap_layer>> layers_;
};

}

#endif // LAYER_LIST_MODEL_HPP