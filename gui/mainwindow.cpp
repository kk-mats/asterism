#include "mainwindow.hpp"
#include "ui_mainwindow.h"


namespace asterism
{

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	QSizePolicy q(QSizePolicy::Preferred, QSizePolicy::Preferred);
	q.setHeightForWidth(true);

	ui->setupUi(this);
	this->scatter_plot_scene_=new scatter_plot_scene(this);
	ui->scatter_plot_view_->setScene(this->scatter_plot_scene_);
	ui->scatter_plot_view_->setSizePolicy(q);
}

MainWindow::~MainWindow()
{
	delete ui;
}

}
