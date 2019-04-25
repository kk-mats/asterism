#ifndef LAYER_LIST_MODEL_HPP
#define LAYER_LIST_MODEL_HPP

#include <QAbstractListModel>
#include <list>

#include "layer/heatmap_layer.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class layer_list_model final
	: public QAbstractListModel
{
	Q_OBJECT

public:
	explicit layer_list_model(QObject *parent=nullptr) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;

	void emplace_clone_size_heatmap_layers(const shared_list<detection_result> &results) noexcept;
	void emplace_clone_size_heatmap_layer(const std::shared_ptr<detection_result> &result) noexcept;
	//void emplace_matching_rate_heatmap_layer(const shared_list<detection_result> &results) noexcept;

signals:
	void current_layer_changed(const std::shared_ptr<heatmap_layer> &layer);

public slots:
	bool insertRows(const int row, const int count, const QModelIndex &parent=QModelIndex()) noexcept override;
	bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) noexcept override;

private:
	shared_list<heatmap_layer> layers_;
};

}

#endif // LAYER_LIST_MODEL_HPP