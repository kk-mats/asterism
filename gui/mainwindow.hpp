#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "scatter_plot_view.hpp"
#include "scatter_plot_scene.hpp"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

namespace asterism
{

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent=nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	scatter_plot_scene *scatter_plot_scene_;
};

}
#endif // MAINWINDOW_HPP
