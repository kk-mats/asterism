#ifndef RESULTS_LIST_VIEW_HPP
#define RESULTS_LIST_VIEW_HPP


#include <QListView>

namespace asterism
{

class results_list_view
	: public QListView
{
	Q_OBJECT

public:
	explicit results_list_view(QWidget *parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags()) noexcept;

};

}

#endif // RESULTS_LIST_VIEW_HPP