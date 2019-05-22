#ifndef LAYER_WIDGET_HPP
#define LAYER_WIDGET_HPP

#include <QComboBox>
#include <QSpinBox>
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
	QPixmap export_current_scatter_plot() noexcept;

public slots:
	void set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept;
	void change_method(const int method_index) noexcept;

signals:
	void method_changed(const int method_index);
	void result_name_changed(const QString &name);

private:
	std::shared_ptr<heatmap_layer> layer_;
	current_grid_detail_widget *current_grid_detail_widget_=new current_grid_detail_widget(this);
	scatter_plot_widget *scatter_plot_widget_;
	QComboBox *method_selector_=new QComboBox(this);
	QSpinBox *grid_size_selector_=new QSpinBox(this);
	color_bar_widget *color_bar_widget_=new color_bar_widget(this);
	QSplitter *splitter_=new QSplitter(this);
	matched_list_widget *matched_list_widget_=new matched_list_widget(this);
};

}

#endif // LAYER_WIDGET_HPP
