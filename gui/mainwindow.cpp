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
	this->scatter_plot_model_->set_heatmap_layer(std::move(h));

	this->scatter_plot_view_=new scatter_plot_view;
	this->scatter_plot_view_->setModel(this->scatter_plot_model_);
	this->scatter_plot_view_->setItemDelegate(new scatter_plot_delegate(this));

	auto *main_layout=new QHBoxLayout;
	main_layout->addWidget(this->scatter_plot_view_);

	auto *central_widget=new QWidget;
	central_widget->setLayout(main_layout);
	this->setCentralWidget(central_widget);

	this->create_actions();
	this->create_menus();

	this->setWindowTitle("Asterism");
}

MainWindow::~MainWindow()
{
}


void MainWindow::open()
{
	auto results=clone_io::read_jcln(QFileDialog::getOpenFileName(this, tr("open file"), QDir::currentPath(), tr("Asterism Project (*.jcln)")), false);
	if(results)
	{
		this->results_=std::move(results.value());
		qInfo().nospace()<<"\n"<<this->results_;
	}
}


void MainWindow::create_actions()
{
	this->open_act_=new QAction(tr("&Open"), this);
	this->open_act_->setShortcuts(QKeySequence::Open);
	this->open_act_->setStatusTip(tr("Open a file"));
	connect(this->open_act_, &QAction::triggered, this, &MainWindow::open);

	this->quit_act_=new QAction(tr("&Quit"), this);
	this->quit_act_->setShortcuts(QKeySequence::Quit);
	this->quit_act_->setStatusTip(tr("Quit"));
	connect(this->quit_act_, &QAction::triggered, this, &QApplication::quit);

}

void MainWindow::create_menus()
{
	this->file_menu_=this->menuBar()->addMenu(tr("&File"));
	this->file_menu_->addAction(this->open_act_);
	this->file_menu_->addSeparator();
	this->file_menu_->addAction(this->quit_act_);
}

}
