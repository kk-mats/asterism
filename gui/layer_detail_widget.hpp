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
	bool setData(const QModelIndex &index, const QVariant &value, int role) noexcept;
	QVariant headerData(int, Qt::Orientation, int) const noexcept override;
	Qt::ItemFlags flags(const QModelIndex &index) const noexcept override;

	std::shared_ptr<heatmap_layer> current_;
	std::vector<std::pair<QString, QString>> details_;

signals:
	void result_name_input(const QString &name);
};


class layer_detail_widget final
	: public QTableView
{
	Q_OBJECT

public:
	explicit layer_detail_widget(QWidget *parent=nullptr) noexcept;

public slots:
	void set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept;
	void change_method(const int method_index) noexcept;
	void change_result_name(const QString &name) noexcept;

signals:
	void result_name_input(const QString &name);

private:
	layer_detail_model *model_=new layer_detail_model(this);
};


}