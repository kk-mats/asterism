#ifndef GRID_PROPERTIES_WIDGET_HPP
#define GRID_PROPERTIES_WIDGET_HPP

#include <QTableView>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QStringList>
#include <QHeaderView>
#include <QPainter>

#include "core/matching_table.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class grid_properties_delegate final
	: public QStyledItemDelegate
{
	Q_OBJECT

public:
	using QStyledItemDelegate::QStyledItemDelegate;

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const noexcept override;
	void setEditorData(QWidget* editor, const QModelIndex& index) const noexcept override;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const noexcept override;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept override;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
	void remove_editor(const int index) noexcept;

signals:
	void index_changed(const int index);

private:
	int previous_=-1;
};

class grid_properties_model final
	: public QAbstractTableModel
{
	Q_OBJECT

public:
	using QAbstractTableModel::QAbstractTableModel;

	static void bind(const std::shared_ptr<matching_table>& matching_table) noexcept;
	
	// inherits from QAbstractTableModel
	int rowCount(const QModelIndex& parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex& parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;

	void change_current_grid(const std::shared_ptr<file>& file1, const std::shared_ptr<file>& file2, const std::shared_ptr<detection_result>& primitive) noexcept;

public slots:
	void change_current_index(const int index) noexcept;

private:
	const QStringList vertical_header={ "ID", "F1.Begin", "F1.End", "F2.Begin", "F2.End", "Similarity" };
	QStringList horizontal_header;
	std::shared_ptr<clone_pair> current_;
	std::shared_ptr<detection_result> primitive_;
	shared_vector<clone_pair> base_;
	std::vector<response> responses_;

	static inline std::shared_ptr<matching_table> matching_table_=nullptr;
};

class grid_properties_widget
	: public QTableView
{
	Q_OBJECT

public:
	grid_properties_widget(QWidget* parent=nullptr) noexcept;

public slots:
	void change_current_grid(const std::shared_ptr<file>& file1, const std::shared_ptr<file>& file2, const std::shared_ptr<detection_result>& primitive) noexcept;

private:
	grid_properties_model* model_=new grid_properties_model(this);
	grid_properties_delegate* grid_properties_delegate_=new grid_properties_delegate(this);
};

}

#endif // GRID_PROPERTIES_WIDGET_HPP