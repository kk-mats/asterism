#pragma once

#include <QTreeView>
#include <QHeaderView>
#include <QAbstractItemModel>

#include "core/matching_table.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class matched_list_model final
	: public QAbstractItemModel
{
	Q_OBJECT

public:
	struct item final
	{
		~item() noexcept;
		int row() const noexcept;
		QVariant data(const int row, const int column) const noexcept;
		QVariant self_;
		item *parent_=nullptr;
		QVector<item *> children_;
	};

	using QAbstractItemModel::QAbstractItemModel;
	~matched_list_model() noexcept;

	static void bind(const std::shared_ptr<file_index> &file_index, const std::shared_ptr<matching_table> &matching_table) noexcept;

	QVariant data(const QModelIndex &index, int role) const noexcept override;
	Qt::ItemFlags flags(const QModelIndex &index) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;
	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const noexcept override;
	QModelIndex parent(const QModelIndex &index) const noexcept override;


public slots:
	void change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept;

private:
	item *root_=new item;
	static inline std::shared_ptr<matching_table> matching_table_=nullptr;
	static inline std::shared_ptr<file_index> file_index_=nullptr;
};

class matched_list_widget
	: public QTreeView
{
	Q_OBJECT

public:
	matched_list_widget(QWidget *parent=nullptr);
	~matched_list_widget();

private:
	matched_list_model *model_=new matched_list_model(this);
};


Q_DECLARE_METATYPE(matched_list_model::item)
}