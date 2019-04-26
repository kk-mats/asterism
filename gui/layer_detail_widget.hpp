#pragma once

#include <QTableView>
#include <QHeaderView>

#include "layer/heatmap_layer.hpp"

namespace asterism
{
class layer_detail_model final
	: public QAbstractTableModel
{
	Q_OBJECT

	friend class layer_detail_widget;

public:
	explicit layer_detail_model(QObject *parent=nullptr) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;

	std::vector<std::pair<QString, QString>> details_;
};


class layer_detail_widget final
	: public QTableView
{
	Q_OBJECT

public:
	explicit layer_detail_widget(QWidget *parent=nullptr) noexcept;

public slots:
	void set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept;

private:
	layer_detail_model *model_=new layer_detail_model(this);
};


}