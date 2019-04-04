#include "detection_result.hpp"

namespace asterism
{

detection_result::detection_result() noexcept
	: id_(new_id())
{}

detection_result::detection_result(const id_t id, result_environment &&context, QHash<clone_pair::id_t, clone_pair> &&clone_pair_table) noexcept
	: id_(id), context_(std::move(context)), clone_pair_table_(std::move(clone_pair_table))
{}

detection_result::id_t detection_result::id() const noexcept
{
	return this->id_;
}

result_environment detection_result::context() const noexcept
{
	return this->context_;
}

QList<clone_pair> detection_result::clone_pairs() const noexcept
{
	return this->clone_pair_table_.values();
}

clone_pair detection_result::operator [](const clone_pair::id_t &id) const&& noexcept
{
	return this->clone_pair_table_[id];
}

clone_pair::id_t detection_result::add(const clone_pair &clone_pair) noexcept
{
	auto p=clone_pair;
	return this->add(std::move(p));
}

clone_pair::id_t detection_result::add(clone_pair &&clone_pair) noexcept
{
	const auto id=clone_pair.id();
	this->clone_pair_table_[id]=std::move(clone_pair);
	return id;
}

void detection_result::make_layer(const uint32_t layer_width) noexcept
{
	this->clone_pair_layer_.make_layer(this->clone_pair_table_.values(), layer_width);
}

const QHash<clone_pair::id_t, clone_pair>& detection_result::clone_pair_table() const noexcept
{
	return this->clone_pair_table_;
}

const clone_pair_grid_layer detection_result::clone_pair_layer() const noexcept
{
	return this->clone_pair_layer_;
}

detection_result::id_t detection_result::new_id() noexcept
{
	auto id=detection_result::id_t(id_ctr_);
	++id_ctr_;
	return id;
}

detection_results::detection_results(const QString &target_path) noexcept
	: target_path_(target_path)
{}

file::id_t detection_results::add(file &&file) noexcept
{
	const auto id=file.id();
	this->file_table_[id]=std::move(file);
	return id;
}

detection_result::id_t detection_results::add(detection_result &&result) noexcept
{
	const auto id=result.id();
	this->result_table_[id]=std::move(result);
	return id;
}

QString detection_results::target_path() const noexcept
{
	return this->target_path_;
}

const QHash<file::id_t, file> detection_results::file_table() const noexcept
{
	return this->file_table_;
}

const QHash<detection_result::id_t, detection_result> detection_results::result_table() const noexcept
{
	return this->result_table_;
}

}
