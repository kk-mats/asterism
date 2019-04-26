#include "layer_widget.hpp"

namespace asterism
{
layer_widget::layer_widget(QWidget *parent) noexcept
	: QWidget(parent)
{
	this->current_grid_detail_widget_=new current_grid_detail_widget(this);
	this->scatter_plot_view_=new scatter_plot_view(this);
	this->scatter_plot_model_=new scatter_plot_model(this);
	this->scatter_plot_view_->setModel(this->scatter_plot_model_);

	auto *layout=new QVBoxLayout(this);
	layout->addWidget(this->current_grid_detail_widget_);
	layout->addWidget(this->scatter_plot_view_);

	this->setLayout(layout);
	connect(this->scatter_plot_view_, &scatter_plot_view::clicked, this->scatter_plot_model_, &scatter_plot_model::select_grid);
	connect(this->scatter_plot_model_, &scatter_plot_model::current_grid_changed, this->current_grid_detail_widget_, &current_grid_detail_widget::change_current_grid);
}


void layer_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	this->scatter_plot_model_->set_layer(layer);
}

}