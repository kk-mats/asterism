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
#include "gui/layer_list_view.hpp"
#include "gui/layer_list_model.hpp"

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

	scatter_plot_widget *scatter_plot_widget_=new scatter_plot_widget(this);

	layer_list_view *layer_list_view_=new layer_list_view(this);
	layer_list_model *layer_list_model_=new layer_list_model(this);
	QDockWidget *layer_list_dock_=new QDockWidget(QStringLiteral("Layer List"), this);

	QMenu *file_menu_;
	QAction *open_act_;
	QAction *quit_act_;

	void initialize_layer_list_dock() noexcept;

	void create_actions();
	void create_menus();

	void update() noexcept;
};

}
#endif // MAINWINDOW_HPP
