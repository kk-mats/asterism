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
	connect(this->layer_widget_, &layer_widget::method_changed, this->layer_detail_widget_, &layer_detail_widget::change_method);
	connect(this->layer_detail_widget_, &layer_detail_widget::result_name_input, this->layer_list_widget_, &layer_list_widget::change_result_name);
	connect(this->layer_list_widget_, &layer_list_widget::result_name_changed, this->layer_detail_widget_, &layer_detail_widget::change_result_name);
	connect(this->layer_list_widget_, &layer_list_widget::result_name_changed, this->layer_widget_, &layer_widget::result_name_changed);

	this->create_actions();
	this->create_menus();
	this->setWindowTitle("Asterism");
}

MainWindow::~MainWindow()
{
}


void MainWindow::open_project() noexcept
{
	if(auto filepath=QFileDialog::getOpenFileName(this, tr("Open Project"), "X:\\projects\\asterism", tr("Asterism Project (*.jcln)")); !filepath.isEmpty())
	{
		if(auto results=clone_io::read_jcln(filepath); results)
		{
			this->results_=std::move(results.value());
			this->update();
			this->layer_list_widget_->set_clone_size_heatmap_layers(this->results_.results());
	
			return;
		}
	}
}

void MainWindow::open_file() noexcept
{
	if(const auto filepath=QFileDialog::getOpenFileName(this, tr("Open File"), "X:\\projects\\asterism", tr("NiCAD (*.xml);; CCFinderSW (*.json)")); !filepath.isEmpty())
	{
		std::shared_ptr<detection_result> result;
		if(filepath.endsWith(".xml"))
		{
			result=clone_io::read_nicad(filepath, this->results_);
		}
		else if(filepath.endsWith(".json"))
		{
			result=clone_io::read_json(filepath, this->results_);
		}

		if(result)
		{
			this->update();
			this->layer_list_widget_->emplace_clone_size_heatmap_layer(result);
			return;
		}
	}
}

void MainWindow::fuse_results() noexcept
{
	if(const auto filepath=QFileDialog::getSaveFileName(this, tr("Export Fusion Result"), "X:\\projects\\asterism", tr(".csv")); !filepath.isEmpty())
	{
		clone_io::write_csv(filepath, this->results_.fuse(), this->results_.target_path());
	}
}

void MainWindow::export_current_scatter_plot() noexcept
{
	if(!this->layer_list_widget_->currentIndex().isValid())
	{
		return;
	}

	if(const auto filepath=QFileDialog::getSaveFileName(this, tr("Export Current Scatter Plot"), "X:\\projects\\asterism", tr("PNG (*.png);; Bitmap(*bmp)")); !filepath.isEmpty())
	{
		auto b=this->layer_widget_->export_current_scatter_plot().toImage();
		
		if(!b.isNull())
		{
			auto f=b.save(filepath);
			f=!f;
		}
	}
}

void MainWindow::remove(const std::shared_ptr<detection_result> &result) noexcept
{
	this->results_.remove(result);
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
	this->open_project_act_=new QAction(tr("Open &Project"), this);
	this->open_project_act_->setShortcuts(QKeySequence::Open);
	this->open_project_act_->setStatusTip(tr("Open project"));
	connect(this->open_project_act_, &QAction::triggered, this, &MainWindow::open_project);

	this->open_file_act_=new QAction(tr("&Open File"), this);
	this->open_file_act_->setShortcuts(QKeySequence::Open);
	this->open_file_act_->setStatusTip(tr("Open file"));
	connect(this->open_file_act_, &QAction::triggered, this, &MainWindow::open_file);

	//this->fuse_results_act_=new QAction(tr("&Fuse Results"), this);
	//connect(this->fuse_results_act_, &QAction::triggered, this, &MainWindow::fuse_results);

	this->export_current_scatter_plot_act_=new QAction(tr("Export Current Scatter Plot"), this);
	this->export_current_scatter_plot_act_->setStatusTip(tr("Export current scatter plot as an image"));
	connect(this->export_current_scatter_plot_act_, &QAction::triggered, this, &MainWindow::export_current_scatter_plot);

	this->quit_act_=new QAction(tr("&Quit"), this);
	this->quit_act_->setShortcuts(QKeySequence::Quit);
	this->quit_act_->setStatusTip(tr("Quit"));
	connect(this->quit_act_, &QAction::triggered, this, &QApplication::quit);

	this->invoke_external_tool_act_=new QAction(tr("&Invoke External Tools"), this);
	this->invoke_external_tool_act_->setStatusTip(tr("External Tools Preferences"));
	this->invoke_external_tool_act_->setStatusTip(tr("Invoke External Tool"));
	//connect(this->invoke_external_tool_act_, &QAction::triggered, this, &);
}

void MainWindow::create_menus() noexcept
{
	this->file_menu_=this->menuBar()->addMenu(tr("&File"));
	this->file_menu_->addAction(this->open_project_act_);
	this->file_menu_->addAction(this->open_file_act_);
	this->file_menu_->addSeparator();
	this->export_menu_=this->file_menu_->addMenu(tr("Export"));
	//this->export_menu_->addAction(this->fuse_results_act_);
	this->export_menu_->addAction(this->export_current_scatter_plot_act_);
	this->file_menu_->addSeparator();
	this->file_menu_->addAction(this->quit_act_);

	this->tools_=this->menuBar()->addMenu(tr("Tools"));
	this->tools_->addAction(this->invoke_external_tool_act_);
}

void MainWindow::update() noexcept
{
	this->results_.update_layers();
	this->layer_list_widget_->update_layers();
	this->layer_widget_->update_layer();
}

}
