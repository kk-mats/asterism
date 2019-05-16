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

#include "gui/layer_widget.hpp"
#include "gui/layer_list_widget.hpp"
#include "gui/layer_detail_widget.hpp"

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

	void remove(const std::shared_ptr<detection_result> &result) noexcept;

private:
	detection_results results_;
	std::shared_ptr<detection_result> current_layer_=nullptr;

	layer_widget *layer_widget_;

	layer_list_widget *layer_list_widget_=new layer_list_widget(this);
	QDockWidget *layer_list_dock_=new QDockWidget(QStringLiteral("Detection Results"), this);

	layer_detail_widget *layer_detail_widget_=new layer_detail_widget(this);
	QDockWidget *layer_detail_dock_=new QDockWidget(QStringLiteral("Detection Result Details"), this);

	QMenu *file_menu_;
	QAction *open_project_act_;
	QAction *open_file_act_;
	QMenu *export_menu_;
	QAction *fuse_results_act_;
	QAction *quit_act_;
	   
	void initialize_docks() noexcept;

	void create_actions() noexcept;
	void create_menus() noexcept;

	void update() noexcept;
};

}
#endif // MAINWINDOW_HPP
