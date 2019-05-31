#ifndef GRID_PROPERTIES_WIDGET_HPP
#define GRID_PROPERTIES_WIDGET_HPP

#include <QTableView>
#include <QItemDelegate>
#include <QComboBox>
#include <QStringList>

#include "core/matching_table.hpp"
#include "model/detection_result.hpp"

namespace asterism
{

class grid_properties_delegate final
	: public QItemDelegate
{
public:
	grid_properties_delegate(const int size, QWidget *parent) noexcept;
	using QItemDelegate::~QItemDelegate;

	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const noexcept override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const noexcept override;

signals:
	void index_changed(const int index);

private:
	int n_;
};

class grid_properties_model final
	: public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit grid_properties_model(QWidget *parent=nullptr) noexcept;

	static void bind(const std::shared_ptr<matching_table> &matching_table) noexcept;

	int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const noexcept override;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const noexcept override;

public slots:
	void change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept;
	void change_current_index(const int index) noexcept;

private:
	const QStringList vertical_header={"F1.Begin", "F1.End", "F2.Begin", "F2.End", "Similarity"};
	QStringList horizontal_header;
	int base_index_=0;
	QVector<query> base_;
	QVector<response> others_;

	static inline std::shared_ptr<matching_table> matching_table_=nullptr;
};
class grid_properties_dock :
	public QDockWidget
{
};

};

#endif // GRID_PROPERTIES_WIDGET_HPP