#include "layer_widget.hpp"

namespace asterism
{
layer_widget::layer_widget(const detection_results *results, QWidget *parent) noexcept
	: QWidget(parent)
{
	this->scatter_plot_widget_=new scatter_plot_widget(results);

	this->method_selector_->addItem("Clone Pair Size");
	this->method_selector_->addItem("Matching Rate");
	this->method_selector_->setDisabled(true);

	auto *colorize_method_label=new QLabel(tr("Colorize Method: "), this);
	auto *bottom_layout=new QHBoxLayout;
	bottom_layout->addWidget(colorize_method_label);
	bottom_layout->addWidget(this->method_selector_);
	bottom_layout->addStretch();

	auto *layout=new QVBoxLayout;
	layout->addWidget(this->current_grid_detail_widget_);
	layout->addWidget(this->scatter_plot_widget_);
	layout->addLayout(bottom_layout);

	this->setLayout(layout);
	
	connect(this->method_selector_, qOverload<int>(&QComboBox::currentIndexChanged), this->scatter_plot_widget_, &scatter_plot_widget::change_method);
	connect(this->scatter_plot_widget_, &scatter_plot_widget::current_grid_changed, this->current_grid_detail_widget_, &current_grid_detail_widget::change_current_grid);
}


void layer_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->scatter_plot_widget_->set_layer(layer);
	this->method_selector_->setEnabled(true);
}

void layer_widget::update_layer() noexcept
{
	this->scatter_plot_widget_->update_layer();
}

}