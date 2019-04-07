#include "mainwindow.hpp"


namespace asterism
{

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	heatmap_layer h(2);
	h[grid_1d_coordinate(file::id_t(0))]=QColor(0, 0, 0);
	h[grid_1d_coordinate(file::id_t(1))]=QColor(255, 0, 0);
	h[grid_1d_coordinate(file::id_t(2))]=QColor(0, 255, 0);

	this->scatter_plot_model_=new scatter_plot_model(this);
	this->scatter_plot_model_->set_heatmap_layer(h);

	this->scatter_plot_view_=new scatter_plot_view;
	this->scatter_plot_view_->setModel(this->scatter_plot_model_);
	this->scatter_plot_view_->setItemDelegate(new scatter_plot_delegate(this));

	auto *main_layout=new QHBoxLayout;
	main_layout->addWidget(this->scatter_plot_view_);

	qDebug()<<this->scatter_plot_view_->verticalHeader()->sectionSize(0);
	qDebug()<<this->scatter_plot_view_->horizontalHeader()->sectionSize(0);

	auto *central_widget=new QWidget;
	central_widget->setLayout(main_layout);
	this->setCentralWidget(central_widget);

	this->setWindowTitle("Asterism");
}

MainWindow::~MainWindow()
{
}

}
