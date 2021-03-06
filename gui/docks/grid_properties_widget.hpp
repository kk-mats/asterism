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
#include <QBoxLayout>

#include "core/matching_table.hpp"
#include "model/detection_result.hpp"
#include "clone_viewer_widget.hpp"

namespace asterism
{

class grid_properties_delegate final
	: public QItemDelegate
{
	Q_OBJECT

public:
	using QItemDelegate::QItemDelegate;

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const noexcept override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const noexcept override;
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

	static void bind(const std::shared_ptr<matching_table> &matching_table) noexcept;
	
	// inherits from QAbstractTableModel
	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const noexcept override;
	bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;
	Qt::ItemFlags flags(const QModelIndex &index) const noexcept override;

	void change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept;

	static bool is_base_selector(const QModelIndex &index) noexcept;

public slots:
	void activate_index(const int index) noexcept;

private:
	const QStringList vertical_header={"ID", "F1.Begin", "F1.End", "F2.Begin", "F2.End", "Similarity"};
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
	grid_properties_widget(QWidget *parent=nullptr) noexcept;

public slots:
	void change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept;

private:
	grid_properties_model *model_=new grid_properties_model(this);
};





class grid_property_table_model final
	: public QAbstractTableModel
{
	Q_OBJECT
public:
	using QAbstractTableModel::QAbstractTableModel;

	static void bind(const std::shared_ptr<matching_table> &matching_table) noexcept;
	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;
	
	void change_current_grid(const shared_vector<clone_pair> &base, const std::shared_ptr<detection_result> &primitive) noexcept;
	void change_base(const int index) noexcept;
	std::vector<response> responses() const noexcept;

private:
	const QStringList vertical_header={"ID", "F1.Begin", "F1.End", "F2.Begin", "F2.End", "Similarity"};
	QStringList horizontal_header;
	int current_=-1;
	std::shared_ptr<detection_result> primitive_;
	shared_vector<clone_pair> base_;
	std::vector<response> responses_;

	static inline std::shared_ptr<matching_table> matching_table_=nullptr;

	bool equals_to_base(const std::shared_ptr<clone_pair> &p, const int row) const noexcept;
};


class grid_property_table_widget final
	: public QTableView
{
	Q_OBJECT
public:
	explicit grid_property_table_widget(QWidget *parent=nullptr) noexcept;
	void change_current_grid(const shared_vector<clone_pair> &base, const std::shared_ptr<detection_result> &primitive) noexcept;
	std::vector<response> responses() const noexcept;

public slots:
	void change_base(const int index) noexcept;

private:
	grid_property_table_model *model_=new grid_property_table_model(this);
};


class grid_property_widget final
	: public QWidget
{
	Q_OBJECT
public:
	explicit grid_property_widget(QWidget *parent=nullptr) noexcept;

public slots:
	void change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept;
	
private:
	QComboBox *base_selector_=new QComboBox(this);
	QPushButton *view_button_=new QPushButton(tr("View fragments"), this);
	grid_property_table_widget *grid_property_table_=new grid_property_table_widget(this);
	clone_viewer_widget *clone_viewer_window_=new clone_viewer_widget;
};

}

#endif // GRID_PROPERTIES_WIDGET_HPP