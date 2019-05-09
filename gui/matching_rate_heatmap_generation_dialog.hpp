#ifndef MATCHING_RATE_HEATMAP_GENERATION_DIALOG_HPP
#define MATCHING_RATE_HEATMAP_GENERATION_DIALOG_HPP

#include <QDialog>


namespace asterism
{


class matching_rate_heatmap_generation_dialog
	: public QDialog
{
	Q_OBJECT

public:
	matching_rate_heatmap_generation_dialog(QWidget *parent=nullptr);
	~matching_rate_heatmap_generation_dialog();
};

}


#endif // MATCHING_RATE_HEATMAP_GENERATION_DIALOG_HPP