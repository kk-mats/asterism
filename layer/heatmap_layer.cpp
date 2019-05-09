#include "heatmap_layer.hpp"

namespace asterism
{

heatmap_layer::clone_pair_size::clone_pair_size(const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->make(primitive);
}

int heatmap_layer::clone_pair_size::min() const noexcept
{
	return this->min_;
}

int heatmap_layer::clone_pair_size::max() const noexcept
{
	return this->max_;
}

std::vector<std::pair<QString, QString>> heatmap_layer::clone_pair_size::details() const noexcept
{
	return
	{
		{"clone pair size min", QString::number(this->min_)},
		{"clone pair size max", QString::number(this->max_)},
		{"clone pair size sum", QString::number(this->sum_)}
	};
}

bool heatmap_layer::clone_pair_size::update(const std::shared_ptr<detection_result> &primitive) noexcept
{
	const auto low=QColor(204, 255, 144);
	const auto high=QColor(233, 30, 30);
	color_selector selector(Qt::white, 0);
	if(0<this->min_)
	{
		selector.set_anchor(Qt::white, this->min_-1);
		selector.set_anchor(low, this->min_);
	}
	else
	{
		selector.set_anchor(low, 1);
	}

	selector.set_anchor(high, this->max_);

	this->width_=primitive->clone_pair_layer()->width();
	this->values_.resize(primitive->clone_pair_layer()->size());
	for(auto i=this->begin1d(), end=this->end1d(); i!=end; ++i)
	{
		if(auto color=selector.color_at((*primitive->clone_pair_layer())[i].size()); !color)
		{
			qCritical()<<heatmap_generating_error::color_index_out_of_range;
			return false;
		}
		else
		{
			(*this)[i]=color.value();
		}
	}
	return true;
}

void heatmap_layer::clone_pair_size::make(const std::shared_ptr<detection_result> &primitive) noexcept
{
	for(const auto &g:*primitive->clone_pair_layer())
	{
		this->sum_+=g.size();
		if(this->min_>g.size())
		{
			this->min_=g.size();
		}
		if(this->max_<g.size())
		{
			this->max_=g.size();
		}
	}
	this->update(primitive);
}

heatmap_layer::matching_rate::matching_rate(const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->update(primitive);
}

int heatmap_layer::matching_rate::average_matching_rate() const noexcept
{
	return this->average_matching_rate_;
}

std::vector<std::pair<QString, QString>> heatmap_layer::matching_rate::details() const noexcept
{
	return
	{
		{"average_matching_rate", QString::number(this->average_matching_rate_)}
	};
}

bool heatmap_layer::matching_rate::update(const std::shared_ptr<detection_result> &primitive) noexcept
{
	return true;
}


heatmap_layer::heatmap_layer(const std::shared_ptr<detection_result> &primitive, const method::clone_pair_size) noexcept
	: primitive_(primitive)
{
	this->value_=std::move(clone_pair_size(this->primitive_));
}

heatmap_layer::heatmap_layer(const std::shared_ptr<detection_result> &primitive, const method::matching_rate) noexcept
	: primitive_(primitive)
{
	this->value_=std::move(matching_rate(this->primitive_));
}

void heatmap_layer::change_method(const method::clone_pair_size) noexcept
{
	this->value_=std::move(clone_pair_size(this->primitive_));
}

void heatmap_layer::change_method(const method::matching_rate) noexcept
{
	this->value_=std::move(matching_rate(this->primitive_));
}

bool heatmap_layer::update() noexcept
{
	return std::visit([&](auto &&h){return h.update(this->primitive_); }, this->value_);
}

int heatmap_layer::method_index() const noexcept
{
	return this->value_.index();
}

QString heatmap_layer::name() const noexcept
{
	return this->primitive_->environment().name();
}

int heatmap_layer::width() const noexcept
{
	return this->primitive_->clone_pair_layer()->width();
}

std::vector<std::pair<QString, QString>> heatmap_layer::details() const noexcept
{
	return std::visit([](const auto &h){ return h.details(); }, this->value_);
}

const QColor& heatmap_layer::operator[](const grid_coordinate &coordinate) const noexcept
{
	return std::visit([&](const auto &h){ return h[coordinate]; }, this->value_);
}

const QColor& heatmap_layer::operator[](const int i) const noexcept
{
	return std::visit([&](const auto &h){ return h[i]; }, this->value_);
}


}
