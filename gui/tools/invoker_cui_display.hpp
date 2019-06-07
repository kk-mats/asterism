#ifndef INVOKER_CUI_DISPLAY_HPP
#define INVOKER_CUI_DISPLAY_HPP

#include <QTextEdit>
#include <QTextStream>
#include <QDialog>
#include <QVector>
#include <QListWidget>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "invoker.hpp"

namespace asterism
{

class invoker_cui_display final
	: public QTextEdit
{
	Q_OBJECT

public:
	invoker_cui_display(QProcess *process, QWidget *parent=nullptr) noexcept;

public slots:
	void read_stdout() noexcept;
	void read_stderr() noexcept;

private:
	QTextStream is_;
	QProcess *process_;
};

class invoker_list_model final
	: public QAbstractListModel
{
	Q_OBJECT
public:
	using QAbstractListModel::QAbstractListModel;

	int	columnCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	int	rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const noexcept override;

	void add_invoker(invoker_t &&invoker) noexcept;

private:
	std::vector<invoker_t> invokers_;
};

class invoker_list_widget final
	: public QListView
{
	Q_OBJECT
public:
	invoker_list_widget(QWidget *parent=nullptr) noexcept;

	void add_invoker(invoker_t &&invoker);
	
private:
	invoker_list_model *model_=new invoker_list_model(this);
};

class invoker_display_widget final
	: public QDialog
{
	Q_OBJECT

public:
	invoker_display_widget(QWidget *parent=nullptr) noexcept;


	void add_invoker(invoker_t &&invoker) noexcept;

protected slots:
	void change_current_page(const QModelIndex &index) noexcept;

private:
	QStackedWidget *displays_=new QStackedWidget(this);
	invoker_list_widget *list_=new invoker_list_widget(this);
};

}

#endif // INVOKER_CUI_DISPLAY_HPP
