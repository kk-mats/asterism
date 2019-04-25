#include "mainwindow.hpp"


namespace asterism
{

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->scatter_plot_view_->setModel(this->scatter_plot_model_);
	this->scatter_plot_view_->setItemDelegate(new scatter_plot_delegate(this));

	this->initialize_layer_list_dock();

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
	if(auto filepath=QFileDialog::getOpenFileName(this, tr("open file"), "X:\\projects\\asterism", tr("Asterism Project (*.jcln)")); !filepath.isEmpty())
	{
		if(auto results=clone_io::read_jcln(filepath); results)
		{
			this->results_=std::move(results.value());
			this->update();
			this->layer_list_model_->emplace_clone_size_heatmap_layers(this->results_.results());

			return;
		}
	}
}


void MainWindow::initialize_layer_list_dock() noexcept
{
	this->layer_list_view_->setModel(this->layer_list_model_);
	this->layer_list_dock_->setWidget(this->layer_list_view_);
	this->addDockWidget(Qt::LeftDockWidgetArea, this->layer_list_dock_, Qt::Vertical);

	connect(this->layer_list_view_, &layer_list_view::clicked, this->layer_list_model_, &layer_list_model::select_layer_ptr);
	connect(this->layer_list_model_, &layer_list_model::current_layer_changed, this->scatter_plot_model_, &scatter_plot_model::set_layer);
	connect(this->scatter_plot_model_, &scatter_plot_model::modelReset, this->scatter_plot_view_, &scatter_plot_view::reset);
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

void MainWindow::update() noexcept
{
	this->results_.update();
}

}
