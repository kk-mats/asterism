#include "scatter_plot_widget.hpp"

namespace asterism
{

void current_grid_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const noexcept
{
	auto op=option;

	if(index.isValid() && op.state&QStyle::State_Selected)
	{
		painter->save();

		const auto bg=index.data(Qt::BackgroundRole).value<QColor>();
		
		painter->fillRect(op.rect, QBrush(bg));
		painter->setPen(QPen(QBrush(Qt::black), 2));
		painter->drawRect(op.rect.adjusted(1, 1, -1, -1));

		painter->restore();
		return;
	}
	QStyledItemDelegate::paint(painter, option, index);
}

scatter_plot_model::scatter_plot_model(QObject *parent) noexcept
	: QAbstractTableModel(parent)
{}

int scatter_plot_model::rowCount(const QModelIndex &) const noexcept
{
	return this->current_layer_!=nullptr ? this->current_layer_->width() : 0;
}

int scatter_plot_model::columnCount(const QModelIndex &) const noexcept
{
	return this->current_layer_!=nullptr ? this->current_layer_->width() : 0;
}

QVariant scatter_plot_model::data(const QModelIndex &index, int role) const noexcept
{
	if(index.isValid() && role==Qt::BackgroundRole)
	{
		auto r=*this->current_layer_;
		auto c=r[grid_2d_coordinate::to_linear(index.row(), index.column())];
		return c;
	}

	return QVariant();
}

QVariant scatter_plot_model::headerData(int, Qt::Orientation, int role) const noexcept
{
	if(role==Qt::SizeHintRole)
	{
		return QSize(this->grid_size_, this->grid_size_);
	}
	return QVariant();
}

void scatter_plot_model::set_layer(const std::shared_ptr<heatmap_layer> &layer, const QModelIndex &previous) noexcept
{
	this->beginResetModel();
	this->current_layer_=layer;
	this->previous_=previous;
	this->endResetModel();
}

void scatter_plot_model::change_method(const int method_index) noexcept
{
	this->beginResetModel();
	if(method_index==0)
	{
		this->current_layer_->change_method(heatmap_layer::method::clone_pair_size());
	}
	else
	{
		this->current_layer_->change_method(heatmap_layer::method::mismatch_rate());
	}
	this->endResetModel();
}

void scatter_plot_model::update_layer()
{
	this->beginResetModel();
	this->endResetModel();
}

scatter_plot_widget::scatter_plot_widget(const detection_results *results, QWidget *parent)
	: QTableView(parent), results_(results)
{
	this->setItemDelegate(new current_grid_delegate(this));	

	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setModel(this->model_);

	this->verticalHeader()->hide();
	this->horizontalHeader()->hide();
	this->set_grid_size();

	connect(this, &scatter_plot_widget::clicked, this, &scatter_plot_widget::select_grid);
}


void scatter_plot_widget::set_layer(const std::shared_ptr<heatmap_layer> &layer) noexcept
{
	const auto previous=this->currentIndex();
	this->model_->set_layer(layer, previous);
	this->setCurrentIndex(previous);
	if(!this->currentIndex().isValid())
	{
		return;
	}

	auto [x, y]=std::minmax(this->results_->file_at(this->currentIndex().row()), this->results_->file_at(this->currentIndex().column()));
	emit current_grid_changed(x, y, this->model_->current_layer_->primitive());
}

void scatter_plot_widget::update_layer() noexcept
{
	this->model_->update_layer();
}

QImage scatter_plot_widget::export_current_scatter_plot() noexcept
{
	const auto width=this->model_->current_layer_->width();
	QImage img(width, width, QImage::Format::Format_ARGB32);
	for(auto y=0; y<width; ++y)
	{
		for(auto x=0; x<width; ++x)
		{
			img.setPixelColor(x, y, (*this->model_->current_layer_)[grid_2d_coordinate::to_linear(x, y)]);
		}
	}

	return img;
}

void scatter_plot_widget::select_grid(const QModelIndex &index) noexcept
{
	if(index.isValid() && this->model_->previous_!=index && (this->model_->previous_.row()!=index.column() || this->model_->previous_.column()!=index.row()))
	{
		this->model_->previous_=index;
		auto [x, y]=std::minmax(this->results_->file_at(index.row()), this->results_->file_at(index.column()));
		emit current_grid_changed(x, y, this->model_->current_layer_->primitive());
	}
}

void scatter_plot_widget::change_grid_size(const int size) noexcept
{
	this->set_grid_size(size);
}

void scatter_plot_widget::change_method(const int method_index) noexcept
{
	const auto current_index=this->currentIndex();
	this->model_->change_method(method_index);
	this->model_->previous_=this->currentIndex();
	this->select_grid(current_index);
}

void scatter_plot_widget::set_grid_size(const int size) noexcept
{
	this->model_->grid_size_=size;
	this->verticalHeader()->setMinimumSectionSize(size);
	this->horizontalHeader()->setMinimumSectionSize(size);
	this->verticalHeader()->setDefaultSectionSize(size);
	this->horizontalHeader()->setDefaultSectionSize(size);
}

}
