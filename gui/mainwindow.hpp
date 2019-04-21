#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QAction>
#include <QMenuBar>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QFileDialog>
#include <QDockWidget>

#include "clone_format/clone_io.hpp"
#include "core/detection_results.hpp"

#include "gui/scatter_plot_view.hpp"
#include "gui/scatter_plot_model.hpp"

#include "gui/results_list_view.hpp"
#include "gui/results_list_model.hpp"

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
	std::shared_ptr<detection_result> current_layer_=nullptr;

	scatter_plot_view *scatter_plot_view_=new scatter_plot_view;
	scatter_plot_model *scatter_plot_model_=new scatter_plot_model(this);

	results_list_view *results_list_view_=new results_list_view(this);
	results_list_model *results_list_model_=new results_list_model(this);
	QDockWidget *results_list_dock_=new QDockWidget(QStringLiteral("Results List"), this);

	QMenu *file_menu_;
	QAction *open_act_;
	QAction *quit_act_;

	void create_actions();
	void create_menus();
	void change_current_layer(const std::shared_ptr<detection_result> &new_result) noexcept;

	void update() noexcept;
};

}
#endif // MAINWINDOW_HPP
