#include "clone_pair.hpp"

namespace asterism
{

// constructor
clone_pair::clone_pair() noexcept
	: fragments_(std::make_pair(fragment(), fragment())), similairty_(0)
{}

clone_pair::clone_pair(const fragment &fragment1, const fragment &fragment2, const unsigned int similarity) noexcept
	: fragments_(std::minmax<fragment>(fragment1, fragment2)), similairty_(similarity)
{}

clone_pair::clone_pair(fragment &&fragment1, fragment &&fragment2, const unsigned int similarity) noexcept
	: fragments_(std::minmax<fragment>(std::move(fragment1), std::move(fragment2))), similairty_(similarity)
{}

QString clone_pair::string() const noexcept
{
	return "("+this->fragment1().string()+"), ("+this->fragment2().string()+"), similarity="+QString::number(this->similarity());
}

bool clone_pair::operator==(const clone_pair &other) const noexcept
{
	return this->fragments_==other.fragments_;
}

bool clone_pair::operator <(const clone_pair &other) const noexcept
{
	return this->fragments_.first<other.fragments_.first;
}

fragment clone_pair::fragment1() const noexcept
{
	return this->fragments_.first;
}

fragment clone_pair::fragment2() const noexcept
{
	return this->fragments_.second;
}

unsigned int clone_pair::similarity() const noexcept
{
	return this->similairty_;
}

uint qHash(const clone_pair &key, uint seed) noexcept
{
	return key.fragments_.first.begin()^seed+key.fragments_.second.begin();
}

QDebug operator <<(QDebug logger, const clone_pair &clone_pair) noexcept
{
	logger.nospace()<<clone_pair.fragments_.first<<", "<<clone_pair.fragments_.second<<", "<<clone_pair.similairty_;
	return logger;
}

float good(const std::shared_ptr<clone_pair> &p1, const std::shared_ptr<clone_pair> &p2) noexcept
{
	return std::min(overlap(p1->fragments_.first, p2->fragments_.first), overlap(p1->fragments_.second, p2->fragments_.second));
}

float ok(const std::shared_ptr<clone_pair> &p1, const std::shared_ptr<clone_pair> &p2) noexcept
{
	return std::min(
		std::max(contained(p1->fragments_.first, p2->fragments_.first), contained(p2->fragments_.first, p1->fragments_.first)),
		std::max(contained(p1->fragments_.second, p2->fragments_.second), contained(p2->fragments_.second, p1->fragments_.second))
	);
}

};
