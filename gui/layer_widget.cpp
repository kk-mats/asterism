#include "layer_widget.hpp"

namespace asterism
{
layer_widget::layer_widget(const detection_results *results, QWidget *parent) noexcept
	: QWidget(parent)
{
	this->scatter_plot_widget_=new scatter_plot_widget(results);

	this->method_selector_->addItem("#Clone Pair");
	this->method_selector_->addItem("Mismatch Rate");
	this->method_selector_->setDisabled(true);

	this->grid_size_selector_->setMinimum(4);
	this->grid_size_selector_->setMaximum(64);
	this->grid_size_selector_->setValue(16);

	auto *colorize_method_label=new QLabel(tr("Colorize Method: "), this);
	auto *method_selector_layout=new QHBoxLayout;
	method_selector_layout->addWidget(colorize_method_label);
	method_selector_layout->addWidget(this->method_selector_);

	auto *grid_size_label_=new QLabel(tr("Grid Size: "), this);
	auto *grid_size_selector_layout=new QHBoxLayout;
	grid_size_selector_layout->addWidget(grid_size_label_);
	grid_size_selector_layout->addWidget(this->grid_size_selector_);

	auto *bottom_layout=new QHBoxLayout;
	bottom_layout->addLayout(method_selector_layout);
	bottom_layout->addLayout(grid_size_selector_layout);
	bottom_layout->addStretch();
	bottom_layout->addWidget(this->color_bar_widget_);
	
	this->splitter_->setOpaqueResize(false);
	this->splitter_->addWidget(this->scatter_plot_widget_);
	this->splitter_->addWidget(this->matched_list_widget_);

	auto *layout=new QVBoxLayout;
	layout->addWidget(this->current_grid_detail_widget_);
	layout->addWidget(this->splitter_);
	layout->addLayout(bottom_layout);
	layout->setStretch(1, 5);

	this->setLayout(layout);
	
	connect(this->method_selector_, qOverload<int>(&QComboBox::currentIndexChanged), this, &layer_widget::change_method);
	connect(this->scatter_plot_widget_, qOverload<const QString&, const QString&, int>(&scatter_plot_widget::current_grid_changed), this->current_grid_detail_widget_, &current_grid_detail_widget::change_current_grid);
	connect(this->scatter_plot_widget_, qOverload<const std::shared_ptr<file>&, const std::shared_ptr<file>&, const std::shared_ptr<detection_result>&>(&scatter_plot_widget::current_grid_changed), (matched_list_model *)this->matched_list_widget_->model(), &matched_list_model::change_current_grid);
	connect(this->grid_size_selector_, qOverload<int>(&QSpinBox::valueChanged), this->scatter_plot_widget_, &scatter_plot_widget::change_grid_size);
	connect(this, &layer_widget::result_name_changed, this->matched_list_widget_, &matched_list_widget::change_result_name);
}


void layer_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->layer_=layer;
	this->scatter_plot_widget_->set_layer(this->layer_);
	if(layer!=nullptr)
	{
		this->method_selector_->setCurrentIndex(this->layer_->method_index());
		this->method_selector_->setEnabled(true);
		this->color_bar_widget_->set_selector(this->layer_->selector(), this->layer_->method_index());
		return;
	}
	this->method_selector_->setDisabled(true);
}

void layer_widget::update_layer() noexcept
{
	this->scatter_plot_widget_->update_layer();
}

QPixmap layer_widget::export_current_scatter_plot() noexcept
{
	return this->scatter_plot_widget_->export_current_scatter_plot();
}

void layer_widget::change_method(const int method_index) noexcept
{
	this->scatter_plot_widget_->change_method(method_index);
	this->color_bar_widget_->set_selector(this->layer_->selector(), method_index);
	emit method_changed(method_index);
}

}