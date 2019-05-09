#pragma once

#include <QTreeView>
#include <QAbstractItemModel>

#include "core/matching_table.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class matched_list_model
	: public QAbstractItemModel
{
	Q_OBJECT

public:
	using QAbstractItemModel::QAbstractItemModel;
	static void bind(const std::shared_ptr<file_index> &file_index, const std::shared_ptr<matching_table> &matching_table) noexcept;

	QVariant data(const QModelIndex &index, int role) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;
	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const noexcept override;
	QModelIndex parent(const QModelIndex &index) const noexcept override;

	struct result_category final
	{
		std::shared_ptr<detection_result> self_;
		shared_vector<clone_pair> children_;

		bool operator ==(const result_category &other) const noexcept;
	};

	struct top_clone_pair final
	{
		std::shared_ptr<clone_pair> self_;
		QVector<result_category> children_;
	};

public slots:
	void change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept;

private:
	std::vector<top_clone_pair> matched_clone_pair_;
	static inline std::shared_ptr<matching_table> matching_table_=nullptr;
	static inline std::shared_ptr<file_index> file_index_=nullptr;
};

class matched_list_widget
	: public QTreeView
{
	Q_OBJECT

public:
	matched_list_widget(QWidget *parent);
	~matched_list_widget();

private:
	matched_list_model *model_=new matched_list_model(this);
};


Q_DECLARE_METATYPE(matched_list_model::result_category)
Q_DECLARE_METATYPE(matched_list_model::top_clone_pair)
}