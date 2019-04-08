#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QAction>
#include <QMenuBar>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QApplication>
#include <QFileDialog>

#include "core/results_operator.hpp"
#include "gui/scatter_plot_view.hpp"
#include "gui/scatter_plot_model.hpp"

namespace asterism
{

class MainWindow
	: public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent=nullptr);
	~MainWindow();

private slots:
	void open();

private:
	detection_results results_;

	scatter_plot_view *scatter_plot_view_;
	scatter_plot_model *scatter_plot_model_;
	QMenu *file_menu_;
	QAction *open_act_;
	QAction *quit_act_;

	void create_actions();
	void create_menus();

};

}
#endif // MAINWINDOW_HPP
