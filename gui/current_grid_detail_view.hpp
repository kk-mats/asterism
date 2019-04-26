#ifndef CURRENT_GRID_DETAIL_VIEW_HPP
#define CURRENT_GRID_DETAIL_VIEW_HPP

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

#include "model/file.hpp"

namespace asterism
{

class current_grid_detail_widget final
	: public QWidget
{
	Q_OBJECT

public:
	explicit current_grid_detail_widget(QWidget *parent=nullptr) noexcept;


public slots:
	void change_current_grid(const QString &filepath1, const QString &filepath2, const int clone_pair_size) noexcept;

signals:
	void filepath1_changed(const QString &filepath1);
	void filepath2_changed(const QString &filepath2);

private:
	QLineEdit *filepath1_=new QLineEdit(this);
	QLineEdit *filepath2_=new QLineEdit(this);
};

}

#endif // CURRENT_GRID_DETAIL_VIEW_HPP
