#ifndef GRID_PROPERTIES_WIDGET_HPP
#define GRID_PROPERTIES_WIDGET_HPP

#include <QTableView>
#include <QItemDelegate>
#include <QComboBox>
#include <QSpinBox>
#include <QStringList>
#include <QHeaderView>
#include <QPainter>
#include <QPushButton>

#include "core/matching_table.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class grid_properties_delegate final
	: public QItemDelegate
{
	Q_OBJECT

public:
	using QItemDelegate::QItemDelegate;

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const noexcept override;
	void setEditorData(QWidget* editor, const QModelIndex& index) const noexcept override;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const noexcept override;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept override;

signals:
	void index_activated(const int index);

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
	bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;
	Qt::ItemFlags flags(const QModelIndex &index) const noexcept override;

	void change_current_grid(const std::shared_ptr<file>& file1, const std::shared_ptr<file>& file2, const std::shared_ptr<detection_result>& primitive) noexcept;

	static bool is_base_selector(const QModelIndex &index) noexcept;

public slots:
	void activate_index(const int index) noexcept;

private:
	const QStringList vertical_header={ "ID", "F1.Begin", "F1.End", "F2.Begin", "F2.End", "Similarity" };
	QStringList horizontal_header;
	int current_=0;
	std::shared_ptr<detection_result> primitive_;
	shared_vector<clone_pair> base_;
	std::vector<response> responses_;

	static inline std::shared_ptr<matching_table> matching_table_=nullptr;

	bool change_current_index(const int index) noexcept;
	bool equals_to_base(const std::shared_ptr<clone_pair> &p, const int row) const noexcept;
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
};

//
//class grid_property_table_model final
//	: public QAbstractTableModel
//{
//	Q_OBJECT
//public:
//	using QAbstractTableModel::QAbstractTableModel;
//
//	static void bind(const std::shared_ptr<matching_table>& matching_table) noexcept;
//	int rowCount(const QModelIndex& parent=QModelIndex()) const noexcept override;
//	int columnCount(const QModelIndex& parent=QModelIndex()) const noexcept override;
//	QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const noexcept override;
//	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;
//	
//	void change_current_grid(const std::shared_ptr<file>& file1, const std::shared_ptr<file>& file2, const std::shared_ptr<detection_result>& primitive) noexcept;
//
//private:
//	const QStringList vertical_header={ "ID", "F1.Begin", "F1.End", "F2.Begin", "F2.End", "Similarity" };
//	QStringList horizontal_header;
//	int current_=0;
//	std::shared_ptr<detection_result> primitive_;
//	shared_vector<clone_pair> base_;
//	std::vector<response> responses_;
//
//	static inline std::shared_ptr<matching_table> matching_table_=nullptr;
//};
//
//
//class grid_property_table_widget final
//	: public QTableView
//{
//	Q_OBJECT
//public:
//	explicit grid_property_table_widget(QWidget *parent=nullptr) noexcept;
//	void change_current_grid(const std::shared_ptr<file>& file1, const std::shared_ptr<file>& file2, const std::shared_ptr<detection_result>& primitive) noexcept;
//
//public slots:
//	void change_current_base(const int i) noexcept;
//
//private:
//};
//
//class grid_property_widget final
//	: public QWidget
//{
//	Q_OBJECT
//public:
//	explicit grid_property_widget(QWidget *parent=nullptr) noexcept;
//
//public slots:
//	void change_current_grid(const std::shared_ptr<file>& file1, const std::shared_ptr<file>& file2, const std::shared_ptr<detection_result>& primitive) noexcept;
//
//private:
//	QComboBox *base_selector_=new QComboBox(this);
//	QPushButton *compare_button_=new QPushButton(tr("Compare"), this);
//	grid_property_table_widget *grid_property_table_=new grid_property_table_widget(this);
//};

}

#endif // GRID_PROPERTIES_WIDGET_HPP