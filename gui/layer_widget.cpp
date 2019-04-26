#include "layer_widget.hpp"

namespace asterism
{
layer_widget::layer_widget(QWidget *parent) noexcept
	: QWidget(parent)
{
	auto *layout=new QVBoxLayout(this);
	layout->addWidget(this->current_grid_detail_widget_);
	layout->addWidget(this->scatter_plot_widget_);

	this->setLayout(layout);
	connect(this->scatter_plot_widget_, &scatter_plot_widget::current_grid_changed, this->current_grid_detail_widget_, &current_grid_detail_widget::change_current_grid);
}


void layer_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->scatter_plot_widget_->set_layer(layer);
}

}