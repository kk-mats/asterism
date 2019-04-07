#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QHBoxLayout>

#include "scatter_plot_view.hpp"
#include "scatter_plot_model.hpp"

namespace asterism
{

class MainWindow
	: public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent=nullptr);
	~MainWindow();

private:
	scatter_plot_view *scatter_plot_view_;
	scatter_plot_model *scatter_plot_model_;
};

}
#endif // MAINWINDOW_HPP
