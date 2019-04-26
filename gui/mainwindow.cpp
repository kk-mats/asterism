#include "mainwindow.hpp"


namespace asterism
{

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->layer_widget_=new layer_widget(&this->results_, this);
	this->setCentralWidget(this->layer_widget_);

	this->initialize_docks();

	connect(this->layer_list_widget_, &layer_list_widget::current_layer_changed, this->layer_widget_, &layer_widget::set_layer);
	connect(this->layer_list_widget_, &layer_list_widget::current_layer_changed, this->layer_detail_widget_, &layer_detail_widget::set_layer);

	this->create_actions();
	this->create_menus();

	this->setWindowTitle("Asterism");
}

MainWindow::~MainWindow()
{
}


void MainWindow::open()
{
	if(auto filepath=QFileDialog::getOpenFileName(this, tr("open file"), "X:\\projects\\asterism", tr("Asterism Project (*.jcln)")); !filepath.isEmpty())
	{
		if(auto results=clone_io::read_jcln(filepath); results)
		{
			this->results_=std::move(results.value());
			this->update();
			this->layer_list_widget_->emplace_clone_size_heatmap_layers(this->results_.results());

			return;
		}
	}
}


void MainWindow::initialize_docks() noexcept
{
	this->layer_list_dock_->setWidget(this->layer_list_widget_);
	this->addDockWidget(Qt::LeftDockWidgetArea, this->layer_list_dock_, Qt::Vertical);
	this->layer_detail_dock_->setWidget(this->layer_detail_widget_);
	this->addDockWidget(Qt::LeftDockWidgetArea, this->layer_detail_dock_, Qt::Vertical);
}

void MainWindow::create_actions() noexcept
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

void MainWindow::create_menus() noexcept
{
	this->file_menu_=this->menuBar()->addMenu(tr("&File"));
	this->file_menu_->addAction(this->open_act_);
	this->file_menu_->addSeparator();
	this->file_menu_->addAction(this->quit_act_);
}

void MainWindow::update() noexcept
{
	this->results_.update();
}

}
