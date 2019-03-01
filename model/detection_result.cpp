#include "detection_result.hpp"

namespace asterism
{

detection_result::detection_result() noexcept
	: id_(new_id())
{}

result_context detection_result::context() const noexcept
{
	return this->context_;
}

QVector<clone_pair> detection_result::clone_pairs() const noexcept
{
	return this->clone_pairs_;
}

uint32_t detection_result::add(const clone_pair &clone_pair) noexcept
{
	this->clone_pairs_.append(clone_pair);
	return this->clone_pairs_.size()-1;
}

uint32_t detection_result::add(clone_pair &&clone_pair) noexcept
{
	this->clone_pairs_.append(std::move(clone_pair));
	return this->clone_pairs_.size()-1;
}

QJsonValue detection_result::to_qjson() const noexcept
{
	QJsonArray json_clone_pairs_array;
	for(const auto &p:this->clone_pairs_)
	{
		json_clone_pairs_array.append(p.to_qjson());
	}

	return QJsonObject
	{
		{"result_id", int(this->id_.index())},
		{"clone_pairs", json_clone_pairs_array}
	};
}

uint32_t detection_result::id_ctr_=0;

detection_result::id_t detection_result::new_id() noexcept
{
	auto id=detection_result::id_t(id_ctr_);
	++id_ctr_;
	return id;
}

}
