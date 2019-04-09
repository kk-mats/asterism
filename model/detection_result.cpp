#include "detection_result.hpp"

namespace asterism
{

detection_result::detection_result() noexcept
{}

detection_result::detection_result(result_environment &&context, shared_set<clone_pair> &&clone_pairs) noexcept
	: context_(std::move(context)), clone_pairs_(std::move(clone_pairs))
{}


clone_pair_grid_layer detection_result::to_layer() const noexcept
{
	return this->clone_pair_grid_layer_;
}

const result_environment& detection_result::context() const noexcept
{
	return this->context_;
}

shared_set<clone_pair>& detection_result::clone_pairs() noexcept
{
	return this->clone_pairs_;
}

const shared_set<clone_pair>& detection_result::clone_pairs() const noexcept
{
	return this->clone_pairs_;
}

}
