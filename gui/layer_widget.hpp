#ifndef LAYER_WIDGET_HPP
#define LAYER_WIDGET_HPP

#include <QComboBox>
#include <QLabel>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "current_grid_detail_widget.hpp"
#include "scatter_plot_widget.hpp"
#include "color_bar_widget.hpp"
#include "matched_clone_pair_list_widget.hpp"

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
	void change_method(const int method_index) noexcept;

signals:
	void method_changed(const int method_index);

private:
	std::shared_ptr<heatmap_layer> layer_;
	current_grid_detail_widget *current_grid_detail_widget_=new current_grid_detail_widget(this);
	scatter_plot_widget *scatter_plot_widget_;
	QComboBox *method_selector_=new QComboBox(this);
	color_bar_widget *color_bar_widget_=new color_bar_widget(this);
	QSplitter *splitter_=new QSplitter(this);
	matched_list_widget *matched_list_widget_=new matched_list_widget(this);
};

}

#endif // LAYER_WIDGET_HPP
