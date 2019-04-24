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
	using QAbstractListModel::QAbstractListModel;

	void set_detection_results(const shared_list<detection_result> &results) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;

private:
	std::list<heatmap_layer> layers_;
};

}

#endif // LAYER_LIST_MODEL_HPP