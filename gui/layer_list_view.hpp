#ifndef LAYER_LIST_VIEW_HPP
#define LAYER_LIST_VIEW_HPP


#include <QListView>

namespace asterism
{

class layer_list_view
	: public QListView
{
	Q_OBJECT

public:
	explicit layer_list_view(QWidget *parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags()) noexcept;

};

}

#endif // LAYER_LIST_VIEW_HPP