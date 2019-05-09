#include "layer_widget.hpp"

namespace asterism
{
layer_widget::layer_widget(const detection_results *results, QWidget *parent) noexcept
	: QWidget(parent)
{
	this->scatter_plot_widget_=new scatter_plot_widget(results);

	this->colorized_rule_selector_->addItem("Clone Pair Size");
	this->colorized_rule_selector_->addItem("Matching Rate");
	this->colorized_rule_selector_->setDisabled(true);

	auto *color_selector_label=new QLabel(tr("Colorized Method: "), this);
	auto *bottom_layout=new QHBoxLayout(this);
	bottom_layout->addWidget(color_selector_label);
	bottom_layout->addWidget(this->colorized_rule_selector_);

	auto *layout=new QVBoxLayout(this);
	layout->addWidget(this->current_grid_detail_widget_);
	layout->addWidget(this->scatter_plot_widget_);
	layout->addWidget(color_selector_label);
	layout->addWidget(this->colorized_rule_selector_);

	this->setLayout(layout);
	connect(this->scatter_plot_widget_, &scatter_plot_widget::current_grid_changed, this->current_grid_detail_widget_, &current_grid_detail_widget::change_current_grid);
	connect(this->colorized_rule_selector_, qOverload<int>(&QComboBox::currentIndexChanged), this->scatter_plot_widget_, &scatter_plot_widget::change_rule);
}


void layer_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->scatter_plot_widget_->set_layer(layer);
	this->colorized_rule_selector_->setCurrentIndex(layer->rule_index());
	this->colorized_rule_selector_->setEnabled(true);
}

void layer_widget::update_layer() noexcept
{
	this->scatter_plot_widget_->update_layer();
}

}