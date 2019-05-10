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
	bottom_layout->addWidget(this->color_bar_widget_);

	auto *plot_layout=new QHBoxLayout;
	plot_layout->addWidget(this->scatter_plot_widget_);
	//plot_layout->addWidget(this->matched_list_widget_);

	auto *layout=new QVBoxLayout;
	layout->addWidget(this->current_grid_detail_widget_);
	layout->addLayout(plot_layout);
	layout->addLayout(bottom_layout);

	this->setLayout(layout);
	
	connect(this->method_selector_, qOverload<int>(&QComboBox::currentIndexChanged), this, &layer_widget::change_method);
	connect(this->scatter_plot_widget_, qOverload<const QString&, const QString&, int>(&scatter_plot_widget::current_grid_changed), this->current_grid_detail_widget_, &current_grid_detail_widget::change_current_grid);
	//connect(this->scatter_plot_widget_, qOverload<const std::shared_ptr<file>&, const std::shared_ptr<file>&, const std::shared_ptr<detection_result>&>(&scatter_plot_widget::current_grid_changed), (matched_list_model *)this->matched_list_widget_->model(), &matched_list_model::change_current_grid);
}


void layer_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->layer_=layer;
	this->scatter_plot_widget_->set_layer(this->layer_);
	this->method_selector_->setCurrentIndex(this->layer_->method_index());
	this->method_selector_->setEnabled(true);
	this->color_bar_widget_->set_selector(this->layer_->selector());
}

void layer_widget::update_layer() noexcept
{
	this->scatter_plot_widget_->update_layer();
}

void layer_widget::change_method(const int method_index) noexcept
{
	((scatter_plot_model *)this->scatter_plot_widget_->model())->change_method(method_index);
	this->color_bar_widget_->set_selector(this->layer_->selector());
	emit method_changed(method_index);
}

}