#include "heatmap_layer.hpp"

namespace asterism
{

clone_size_heatmap_layer::clone_size_heatmap_layer(const std::shared_ptr<detection_result> &primitive) noexcept
	: primitive_(primitive), name_(primitive->environment().name())
{}

QString clone_size_heatmap_layer::name() const noexcept
{
	return this->name_;
}

QString clone_size_heatmap_layer::primitive_name() const noexcept
{
	return this->primitive_->environment().name();
}

QString clone_size_heatmap_layer::primitive_source() const noexcept
{
	return this->primitive_->environment().source();
}

int clone_size_heatmap_layer::min() const noexcept
{
	return this->min_;
}

int clone_size_heatmap_layer::max() const noexcept
{
	return this->max_;
}

bool clone_size_heatmap_layer::update(const file_index &file_index) noexcept
{
	this->max_=(*std::max_element(this->primitive_->clone_pair_layer()->begin(), this->primitive_->clone_pair_layer()->end(), [](const auto&g1, const auto&g2){ return g1.size()<g2.size(); })).size();
	this->min_=(*std::min_element(this->primitive_->clone_pair_layer()->begin(), this->primitive_->clone_pair_layer()->end(), [](const auto&g1, const auto&g2){ return g1.size()<g2.size(); })).size();

	color_selector selector(Qt::white, 0);
	if(0<this->min_)
	{
		selector.set_anchor(Qt::white, this->min_-1);
		selector.set_anchor(Qt::green, this->min_);
	}
	else
	{
		selector.set_anchor(Qt::green, 1);
	}

	selector.set_anchor(Qt::red, this->max_);

	for(auto i=this->begin1d(), end=this->end1d(); i!=end; ++i)
	{
		if(auto color=selector.color_at((*this->primitive_->clone_pair_layer())[i].size()); !color)
		{
			qCritical()<<heatmap_generating_error::color_index_out_of_range;
			return false;
		}
		else
		{
			(*this)[i]=color.value();
		}
	}
}

matching_rate_heatmap_layer::matching_rate_heatmap_layer(const std::shared_ptr<detection_result> &primitive1, const std::shared_ptr<detection_result> &primitive2) noexcept
	: primitive1_(primitive1), primitive2_(primitive2)
{}

QString matching_rate_heatmap_layer::name() const noexcept
{
	return this->name_;
}

QString matching_rate_heatmap_layer::primitive1_name() const noexcept
{
	return this->primitive1_->environment().name();
}

QString matching_rate_heatmap_layer::primitive1_source() const noexcept
{
	return this->primitive1_->environment().source();
}

QString matching_rate_heatmap_layer::primitive2_name() const noexcept
{
	return this->primitive1_->environment().name();
}

QString matching_rate_heatmap_layer::primitive2_source() const noexcept
{
	return this->primitive1_->environment().source();
}

bool matching_rate_heatmap_layer::update(const file_index &file_index) noexcept
{
	return false;
}

QString heatmap_layer_name_visitor::operator()(const clone_size_heatmap_layer &h) noexcept
{
	return h.name();
}

QString heatmap_layer_name_visitor::operator()(const matching_rate_heatmap_layer &h) noexcept
{
	return h.name();
}

}
