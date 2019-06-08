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
	connect(this->layer_detail_widget_, &layer_detail_widget::result_name_input, this->layer_list_widget_, &layer_list_widget::change_result_name);
	connect(this->layer_list_widget_, &layer_list_widget::result_name_changed, this->layer_detail_widget_, &layer_detail_widget::change_result_name);
	connect(this->layer_list_widget_, &layer_list_widget::result_name_changed, this->layer_widget_, &layer_widget::result_name_changed);
	connect(this->layer_widget_, &layer_widget::current_grid_changed, this->grid_properties_widget_, &grid_properties_widget::change_current_grid);
	connect(this->layer_widget_, &layer_widget::method_changed, this->layer_detail_widget_, &layer_detail_widget::change_method);
	
	matched_list_model::bind(this->results_.matching_pair_table());
	grid_properties_model::bind(this->results_.matching_pair_table());

	this->create_actions();
	this->create_menus();
	this->setWindowTitle("Asterism");
}

MainWindow::~MainWindow()
{
}


void MainWindow::open_project() noexcept
{
	if(auto filepath=QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("Asterism Project (*.jcln)")); !filepath.isEmpty())
	{
		if(auto results=clone_io::read_jcln(filepath); results)
		{
			this->results_=std::move(results.value());
			matched_list_model::bind(this->results_.matching_pair_table());
			grid_properties_model::bind(this->results_.matching_pair_table());
			this->update();
			this->layer_list_widget_->set_clone_size_heatmap_layers(this->results_.results());
	
			return;
		}
	}
}

void MainWindow::open_file() noexcept
{
	if(const auto filepath=to_canonical_file_path(QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("NiCAD (*.xml);; CCVolti(*.csv);; CCFinderSW (*.json)"))); !filepath.isEmpty())
	{
		this->load_file(filepath);
	}
}

void MainWindow::fuse_results() noexcept
{
	if(const auto filepath=QFileDialog::getSaveFileName(this, tr("Export Fusion Result"), "", tr(".csv")); !filepath.isEmpty())
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

	if(const auto filepath=QFileDialog::getSaveFileName(this, tr("Export Current Scatter Plot"), "", tr("PNG (*.png);; Bitmap(*bmp)")); !filepath.isEmpty())
	{
		auto b=this->layer_widget_->export_current_scatter_plot().save(filepath);
	}
}

void MainWindow::external_tools_settings() noexcept
{
	(new external_tools_settings_dialog(this))->exec();
}

void MainWindow::invoke_ccfinderx() noexcept
{
	this->show_invoke_dialog(new invoke_ccfinderx_dialog(this->results_.target_path(), this));
}

void MainWindow::invoke_ccvolti() noexcept
{
	this->show_invoke_dialog(new invoke_ccvolti_dialog(this->results_.target_path(), this));
}

void MainWindow::invoke_ccfindersw() noexcept
{
	this->show_invoke_dialog(new invoke_ccfindersw_dialog(this->results_.target_path(), this));
}

void MainWindow::invoke_nicad() noexcept
{
	this->show_invoke_dialog(new invoke_nicad_dialog(this->results_.target_path(), this));
}

void MainWindow::remove(const std::shared_ptr<detection_result> &result) noexcept
{
	this->results_.remove(result);
}

void MainWindow::load_file(const QString &filepath) noexcept
{
	std::shared_ptr<detection_result> result;
	if(const auto extension=QFileInfo(filepath).suffix(); extension=="xml")
	{
		result=clone_io::read_nicad(filepath, this->results_);
	}
	else if(extension=="csv")
	{
		result=clone_io::read_ccvolti(filepath, this->results_);
	}
	else if(extension=="json")
	{
		result=clone_io::read_ccfindersw(filepath, this->results_);
	}

	if(result)
	{
		this->update();
		this->layer_list_widget_->emplace_clone_size_heatmap_layer(result);
	}
}

void MainWindow::initialize_docks() noexcept
{
	this->layer_list_dock_->setWidget(this->layer_list_widget_);
	this->addDockWidget(Qt::LeftDockWidgetArea, this->layer_list_dock_, Qt::Vertical);
	this->layer_detail_dock_->setWidget(this->layer_detail_widget_);
	this->addDockWidget(Qt::LeftDockWidgetArea, this->layer_detail_dock_, Qt::Vertical);
	this->grid_properties_dock_->setWidget(this->grid_properties_widget_);
	this->addDockWidget(Qt::BottomDockWidgetArea, this->grid_properties_dock_, Qt::Horizontal);
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

	
	this->invoke_ccfinderx_act_=new QAction(tr("Invoke CCFinderX"));
	this->invoke_ccfinderx_act_->setStatusTip(tr("Invoke CCFidnerX"));
	connect(this->invoke_ccfinderx_act_, &QAction::triggered, this, &MainWindow::invoke_ccfinderx);

	this->invoke_nicad_act_=new QAction(tr("Invoke NiCAD"));
	this->invoke_nicad_act_->setStatusTip(tr("Invoke NiCAD"));
	connect(this->invoke_nicad_act_, &QAction::triggered, this, &MainWindow::invoke_nicad);

	this->invoke_ccvolti_act_=new QAction(tr("Invoke CCVolti"));
	this->invoke_ccvolti_act_->setStatusTip(tr("Invoke CCVolti"));
	connect(this->invoke_ccvolti_act_, &QAction::triggered, this, &MainWindow::invoke_ccvolti);
	
	this->invoke_ccfindersw_act_=new QAction(tr("Invoke CCFinderSW"));
	this->invoke_ccfindersw_act_->setStatusTip(tr("Invoke CCFinderSW"));
	connect(this->invoke_ccfindersw_act_, &QAction::triggered, this, &MainWindow::invoke_ccfindersw);

	this->invoke_from_a_setting_file_act_=new QAction(tr("Invoke From A Setting File"));
	this->invoke_from_a_setting_file_act_->setStatusTip(tr("Invoke Clone Detector From A JSON-like Setting File"));

	this->options_act_=new QAction(tr("Options"));
	this->options_act_->setStatusTip(tr("Tools Options"));
	connect(this->options_act_, &QAction::triggered, this, &MainWindow::external_tools_settings);


	connect(this->invoker_display_dialog_, &invoker_display_widget::finished_clone_file, [this](const auto &filepath) mutable { this->load_file(filepath); });
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
	this->invoke_external_tool_menu_=this->tools_->addMenu(tr("Invoke External Tool"));
	this->invoke_external_tool_menu_->addAction(this->invoke_ccfinderx_act_);
	this->invoke_external_tool_menu_->addAction(this->invoke_nicad_act_);
	this->invoke_external_tool_menu_->addAction(this->invoke_ccvolti_act_);
	this->invoke_external_tool_menu_->addAction(this->invoke_ccfindersw_act_);
	this->invoke_external_tool_menu_->addSeparator();
	this->invoke_external_tool_menu_->addAction(this->invoke_from_a_setting_file_act_);

	this->tools_->addAction(this->options_act_);
}

void MainWindow::update() noexcept
{
	this->results_.update_layers();
	this->layer_list_widget_->update_layers();
	this->layer_widget_->update_layer();
}

// returns true when this has the target project path
bool MainWindow::request_target_path() noexcept
{
	if(!this->results_.target_path().isEmpty())
	{
		return true;
	}

	if(const auto path=QFileDialog::getExistingDirectory(this, tr("Select target project")); !path.isEmpty())
	{
		this->results_.set_target_path(path);
		return true;
	}
	return false;
}

void MainWindow::show_invoke_dialog(invoke_dialog *d) noexcept
{
	if(d->exec()==QDialog::Accepted)
	{
		this->invoker_display_dialog_->add_invoker(std::move(d->create_invoker()));
		this->invoker_display_dialog_->show();
	}
}

}
