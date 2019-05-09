#ifndef LAYER_WIDGET_HPP
#define LAYER_WIDGET_HPP

#include <QComboBox>

#include "current_grid_detail_widget.hpp"
#include "scatter_plot_widget.hpp"

namespace asterism
{

class layer_widget final
	: public QWidget
{
	Q_OBJECT

public:
	explicit layer_widget(const detection_results *results, QWidget *parent=nullptr) noexcept;
	
	void update_layer() noexcept;

public slots:
	void set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept;

private:
	current_grid_detail_widget *current_grid_detail_widget_=new current_grid_detail_widget(this);
	scatter_plot_widget *scatter_plot_widget_;
	QComboBox *colorized_rule_selector_=new QComboBox(this);
};

}

#endif // LAYER_WIDGET_HPP
