#ifndef LAYER_LIST_WIDGET_HPP
#define LAYER_LIST_WIDGET_HPP


#include <QMenu>
#include <QListView>
#include <QAbstractListModel>

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

	bool removeRows(int row, int count, const QModelIndex &parent=QModelIndex()) override;
	int rowCount(const QModelIndex &parent=QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;

	int current_index_=-1;
	shared_list<heatmap_layer> layers_;

public slots:
	bool insertRows(const int row, const int count, const QModelIndex &parent=QModelIndex()) noexcept override;
	bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) noexcept override;
};


class layer_list_widget final
	: public QListView
{
	Q_OBJECT

public:
	explicit layer_list_widget(QWidget *parent=nullptr) noexcept;

	void update_layers() noexcept;

	void set_clone_size_heatmap_layers(const shared_list<detection_result> &results) noexcept;

	void emplace_clone_size_heatmap_layers(const shared_list<detection_result> &results) noexcept;
	void emplace_clone_size_heatmap_layer(const std::shared_ptr<detection_result> &result) noexcept;
	//void emplace_matching_rate_heatmap_layer(const shared_list<detection_result> &results) noexcept;

public slots:
	void select_layer_ptr(const QModelIndex &index) noexcept;

private slots:
	void show_context_menu(const QPoint &pos) noexcept;
	void click_rename() noexcept;
	void click_remove() noexcept;

signals:
	void current_layer_changed(const std::shared_ptr<heatmap_layer> &layer);
	void remove(const std::shared_ptr<detection_result> &result);

private:
	layer_list_model *model_=new layer_list_model(this);
/*
	QMenu *context_menu_=new QMenu(this);
	QAction *rename_act_=new QAction(tr("Rename"), this);
	QAction *remove_act_=new QAction(tr("Remove"), this);*/
};

}

#endif // LAYER_LIST_WIDGET_HPP