#ifndef CURRENT_GRID_DETAIL_WIDGET_HPP
#define CURRENT_GRID_DETAIL_WIDGET_HPP

#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

#include "model/detection_result.hpp"

namespace asterism
{

class current_grid_detail_widget final
	: public QWidget
{
	Q_OBJECT

public:
	explicit current_grid_detail_widget(QWidget *parent=nullptr) noexcept;
	
public slots:
	void change_current_grid(const std::shared_ptr<file> &file1, const std::shared_ptr<file> &file2, const std::shared_ptr<detection_result> &primitive) noexcept;

private:
	QLineEdit *filepath1_=new QLineEdit(this);
	QLineEdit *filepath2_=new QLineEdit(this);
};

}

#endif // CURRENT_GRID_DETAIL_WIDGET_HPP
