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

#include "central.hpp"
#include "docks.hpp"
#include "tools.hpp"

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
	void open_project() noexcept;
	void open_file() noexcept;
	void fuse_results() noexcept;
	void export_current_scatter_plot() noexcept;

	void external_tools_settings() noexcept;
	void invoke_ccfinderx() noexcept;
	void invoke_ccvolti() noexcept;
	void invoke_ccfindersw() noexcept;
	void invoke_nicad() noexcept;

	void remove(const std::shared_ptr<detection_result> &result) noexcept;

private:
	detection_results results_;
	std::shared_ptr<detection_result> current_layer_=nullptr;

	layer_widget *layer_widget_;

	layer_list_widget *layer_list_widget_=new layer_list_widget(this);
	QDockWidget *layer_list_dock_=new QDockWidget(tr("Detection Results"), this);

	layer_detail_widget *layer_detail_widget_=new layer_detail_widget(this);
	QDockWidget *layer_detail_dock_=new QDockWidget(tr("Details"), this);

	grid_properties_widget *grid_properties_widget_=new grid_properties_widget(this);
	QDockWidget *grid_properties_dock_=new QDockWidget(tr("Grid Properties"), this);

	invoker_display_widget *invoker_display_dialog_=new invoker_display_widget(this);

	QMenu *file_menu_;
	QAction *open_project_act_;
	QAction *open_file_act_;
	
	// File.Export
	QMenu *export_menu_;
	QAction *fuse_results_act_;
	QAction *quit_act_;
	QAction *export_current_scatter_plot_act_;


	// Tools
	QMenu *tools_;
	QMenu *invoke_external_tool_menu_;
	QAction *invoke_ccfinderx_act_;
	QAction *invoke_nicad_act_;
	QAction *invoke_ccvolti_act_;
	QAction *invoke_ccfindersw_act_;
	QAction *invoke_from_a_setting_file_act_;
	QAction *options_act_;
	   
	void initialize_docks() noexcept;

	void create_actions() noexcept;
	void create_menus() noexcept;

	void update() noexcept;

	bool request_target_path() noexcept;

	void show_invoke_dialog(invoke_dialog *d) noexcept;
};

}
#endif // MAINWINDOW_HPP
