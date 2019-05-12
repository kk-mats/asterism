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
	class item final
	{
	public:
		item() noexcept=default;
		item(const QVariant &self, const QVariant &text, item *parent) noexcept;
		item(const std::shared_ptr<clone_pair> &self, const QVariant &text, item *parent) noexcept;
		item(const std::shared_ptr<detection_result> &self, const QVariant &text, item *parent) noexcept;
		~item() noexcept;

		int row() const noexcept;
		int column_size() const noexcept;
		int children_size() const noexcept;

		QVariant self(const int i) const noexcept;
		item* parent() const noexcept;
		item* child(const int i) const noexcept;
		QVariant data(const int row, const int column) const noexcept;

		void append_child(item *child) noexcept;
		void emplace_child(const QVariant &child, const QVariant &text) noexcept;
		void emplace_children(const QVector<std::pair<QVariant, QVariant>> &children) noexcept;

	private:

		QVector<QVariant> self_;
		item *parent_=nullptr;
		QVector<item *> children_;

		bool is_string(const int i) const noexcept;
		bool is_int(const int i) const noexcept;
		bool is_clone_pair(const int i) const noexcept;
		bool is_detection_result(const int i) const noexcept;

		QString to_string(const int i) const noexcept;
		int to_int(const int i) const noexcept;
		std::shared_ptr<clone_pair> to_clone_pair(const int i) const noexcept;
		std::shared_ptr<detection_result> to_detection_result(const int i) const noexcept;
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
	item *root_=new item(QStringLiteral(""), "Description", nullptr);;
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