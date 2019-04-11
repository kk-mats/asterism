#include "detection_result.hpp"

namespace asterism
{

detection_result::detection_result() noexcept
{}

detection_result::detection_result(result_environment &&environment, shared_set<clone_pair> &&clone_pairs) noexcept
	: environment_(std::move(environment)), clone_pairs_(std::move(clone_pairs))
{}


clone_pair_grid_layer detection_result::to_layer(const QMap<std::shared_ptr<file>, int> file_index_map) const noexcept
{
	return clone_pair_grid_layer(this->clone_pairs_, file_index_map);
}

const result_environment& detection_result::environment() const noexcept
{
	return this->environment_;
}

shared_set<clone_pair>& detection_result::clone_pairs() noexcept
{
	return this->clone_pairs_;
}

const shared_set<clone_pair>& detection_result::clone_pairs() const noexcept
{
	return this->clone_pairs_;
}

bool detection_result::operator ==(const detection_result &detection_result) const noexcept
{
	return this->environment_.source()==detection_result.environment_.source();
}

uint qHash(const detection_result &key, uint seed) noexcept
{
	return qHash(key.environment().source(), seed);
}

uint qHash(const std::shared_ptr<detection_result> &key, uint seed) noexcept
{
	return qHash(key->environment().source(), seed);
}

QDebug operator <<(QDebug logger, const detection_result &detection_result) noexcept
{
	logger.nospace()<<"{";
	logger.nospace()<<"\tsource="<<detection_result.environment_.source()<<"\n";
	for(const auto &c:detection_result.clone_pairs_)
	{
		logger.nospace()<<"\t"<<*c<<"\n";
	}
	logger.nospace()<<"}\n";
	return logger;
}

}
