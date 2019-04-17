#include "mainwindow.hpp"


namespace asterism
{

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->scatter_plot_model_=new scatter_plot_model(this);

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
	if(auto filepath=QFileDialog::getOpenFileName(this, tr("open file"), "X:\\projects\\asterism", tr("Asterism Project (*.jcln)")); !filepath.isEmpty())
	{
		if(auto results=clone_io::read_jcln(filepath); results)
		{
			this->results_=std::move(results.value());
			this->update();
		}
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

void MainWindow::change_current_layer(const std::shared_ptr<detection_result> &new_result) noexcept
{
	this->current_layer_=new_result;
	if(auto layer=heatmap_layer::colorized_by_clone_pair_size(new_result->clone_pair_layer(), this->results_.file_index_map()); layer)
	{
		this->scatter_plot_model_->set_heatmap_layer(std::move(layer.value()));
	}
}

void MainWindow::update() noexcept
{
	this->results_.update();
	//ToDo
	this->change_current_layer(*this->results_.results().begin());
	this->scatter_plot_model_->update(this->results_.file_index_map());
}

}
