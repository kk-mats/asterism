#include "scatter_plot_view.hpp"

namespace asterism
{

void scatter_plot_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if(index.data().canConvert<QColor>())
	{
		painter->fillRect(option.rect, index.data().value<QColor>());
	}
}

QSize scatter_plot_delegate::sizeHint(const QStyleOptionViewItem &option [[maybe_unused]], const QModelIndex &index [[maybe_unused]]) const
{
	return QSize(grid_size, grid_size);
}

scatter_plot_view::scatter_plot_view(QWidget* parent)
	: QTableView(parent)
{

	this->verticalHeader()->hide();
	this->horizontalHeader()->hide();
	this->verticalHeader()->setMinimumSectionSize(grid_size);
	this->horizontalHeader()->setMinimumSectionSize(grid_size);
	this->verticalHeader()->setDefaultSectionSize(grid_size);
	this->horizontalHeader()->setDefaultSectionSize(grid_size);
}

}
