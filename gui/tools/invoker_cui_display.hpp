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
	invoker_cui_display(invoker_t &&invoker, QWidget *parent=nullptr) noexcept;

public slots:
	void read_stdout() noexcept;
	void read_stderr() noexcept;

signals:
	void error_occored();
	void finished(const bool success);

private:
	QTextStream is_;
	QProcess *process_;
	invoker_t invoker_;
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

	invoker_t* add_invoker(invoker_t &&invoker) noexcept;
	void change_status(const int i, const QString &name) noexcept;

private:
	QStringList names_;
	QVector<invoker_t> invokers_;
};

class invoker_list_widget final
	: public QListWidget
{
	Q_OBJECT
public:
	invoker_list_widget(QWidget *parent=nullptr) noexcept;

	void add_invoker(const invoker_t &invoker) noexcept;
	
public slots:
	void change_status(const int i, const QString &name);

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

signals:
	void finished_clone_file(const QString &clone_file);
	void invoker_status_changed(const int i, const QString &name);

protected slots:
	void change_current_page(const QModelIndex &index) noexcept;

private:
	QStackedWidget *displays_=new QStackedWidget(this);
	invoker_list_widget *list_=new invoker_list_widget(this);
};

}

#endif // INVOKER_CUI_DISPLAY_HPP
