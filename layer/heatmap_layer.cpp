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

color_selector heatmap_layer::clone_pair_size::selector() const noexcept
{
	return this->selector_;
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
	this->width_=primitive->clone_pair_layer()->width();
	this->values_.resize(primitive->clone_pair_layer()->size());
	for(auto i=this->begin1d(), end=this->end1d(); i!=end; ++i)
	{
		if(auto color=this->selector_.color_at((*primitive->clone_pair_layer())[i].size()); !color)
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

	const auto low=QColor(0xf5, 0xfc, 0x94);
	const auto high=QColor(0xff, 0x00, 0x00);
	if(0<this->min_)
	{
		this->selector_.set_anchor(Qt::white, this->min_-1);
		this->selector_.set_anchor(this->min_, low);
	}
	else
	{
		this->selector_.set_anchor(1, low);
	}
	this->selector_.set_anchor(this->max_, high);

	this->update(primitive);
}

void heatmap_layer::matching_rate::bind(const std::shared_ptr<file_index> &file_index, const std::shared_ptr<matching_table> &matching_table) noexcept
{
	file_index_=file_index;
	matching_table_=matching_table;
}

heatmap_layer::matching_rate::matching_rate(const std::shared_ptr<detection_result> &primitive) noexcept
{
	this->update(primitive);
}

int heatmap_layer::matching_rate::average_matching_rate() const noexcept
{
	return this->average_matching_rate_;
}

color_selector heatmap_layer::matching_rate::selector() const noexcept
{
	return selector_;
}

std::vector<std::pair<QString, QString>> heatmap_layer::matching_rate::details() const noexcept
{
	return
	{
		{"average matching rate", QString::number(this->average_matching_rate_)}
	};
}

bool heatmap_layer::matching_rate::update(const std::shared_ptr<detection_result> &primitive) noexcept
{
	const auto no_clone_pair=Qt::white;
	this->width_=primitive->clone_pair_layer()->width();
	this->values_.resize(primitive->clone_pair_layer()->size());

	int matched_all=0;

	for(auto i=this->begin1d(), end=this->end1d(); i!=end; ++i)
	{
		int size=(*primitive->clone_pair_layer())[i].size();
		if(size==0)
		{
			(*this)[i]=no_clone_pair;
			continue;
		}

		int matched=0;
		for(const auto &p:(*primitive->clone_pair_layer())[i])
		{
			if(matching_table_->has_matching_pair(primitive, p, file_index_))
			{
				++matched;
			}
		}

		matched_all+=matched;

		if(auto color=selector_.color_at(matched*100/size); !color)
		{
			qCritical()<<heatmap_generating_error::color_index_out_of_range;
			return false;
		}
		else
		{
			(*this)[i]=color.value();
		}
	}

	this->average_matching_rate_=matched_all*100/primitive->clone_pairs().size();
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

std::shared_ptr<detection_result> heatmap_layer::primitive() const noexcept
{
	return this->primitive_;
}

int heatmap_layer::width() const noexcept
{
	return this->primitive_->clone_pair_layer()->width();
}

color_selector heatmap_layer::selector() const noexcept
{
	return std::visit([&](const auto &h){ return h.selector(); }, this->value_);
}

std::vector<std::pair<QString, QString>> heatmap_layer::details() const noexcept
{
	std::vector<std::pair<QString, QString>> d={
		{"name", this->name()},
		{"source", this->primitive_->environment().source()}
	};
	auto r=std::visit([](const auto &h){ return h.details(); }, this->value_);
	d.insert(d.end(), r.begin(), r.end());

	return d;
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
