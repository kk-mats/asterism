#ifndef LAYER_WIDGET_HPP
#define LAYER_WIDGET_HPP

#include "current_grid_detail_view.hpp"
#include "scatter_plot_view.hpp"
#include "scatter_plot_model.hpp"

namespace asterism
{

class layer_widget final
	: public QWidget
{
	Q_OBJECT

public:
	explicit layer_widget(QWidget *parent=nullptr) noexcept;

public slots:
	void set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept;

private:
	current_grid_detail_widget *current_grid_detail_widget_;
	scatter_plot_view *scatter_plot_view_;
	scatter_plot_model *scatter_plot_model_;
};

}

#endif // LAYER_WIDGET_HPP
