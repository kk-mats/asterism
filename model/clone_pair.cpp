#include "clone_pair.hpp"

namespace asterism
{

// constructor
clone_pair::clone_pair() noexcept
	: id_(0), fragments_(qMakePair(fragment(), fragment())), similairty_(0)
{}

clone_pair::clone_pair(const fragment &fragment1, const fragment &fragment2, const unsigned int similarity) noexcept
	: id_(new_id()), fragments_(canonical(fragment1, fragment2)), similairty_(similarity)
{}

clone_pair::clone_pair(fragment &&fragment1, fragment &&fragment2, const unsigned int similarity) noexcept
	: id_(new_id()), fragments_(canonical(fragment1, fragment2)), similairty_(similarity)
{}

bool clone_pair::operator ==(const clone_pair &other) const noexcept
{
	return this->id_==other.id_;
}

bool clone_pair::operator <(const clone_pair &other) const noexcept
{
	return this->fragments_.first<other.fragments_.first;
}

clone_pair::id_t clone_pair::id() const noexcept
{
	return this->id_;
}

fragment clone_pair::fragment1() const noexcept
{
	return this->fragments_.first;
}

fragment clone_pair::fragment2() const noexcept
{
	return this->fragments_.first;
}

unsigned int clone_pair::similarity() const noexcept
{
	return this->similairty_;
}

clone_pair::id_t clone_pair::new_id() noexcept
{
	auto id=clone_pair::id_t(id_ctr_);
	++id_ctr_;
	return id;
}

QPair<fragment, fragment> clone_pair::canonical(const fragment &fragment1, const fragment &fragment2) noexcept
{
	fragment f1=fragment1, f2=fragment2;
	return this->canonical(std::move(f1), std::move(f2));
}

QPair<fragment, fragment> clone_pair::canonical(fragment &&fragment1, fragment &&fragment2) noexcept
{
	return fragment1<fragment2 ?
				qMakePair(fragment1, fragment2) :
				qMakePair(fragment2, fragment1);
}

uint qHash(const clone_pair::id_t &key, [[maybe_unused]]uint seed) noexcept
{
	return key;
}

uint qHash(const clone_pair &key, [[maybe_unused]]uint seed) noexcept
{
	return key.id();
}

float good(const clone_pair &p1, const clone_pair &p2) noexcept
{
	return std::min(overlap(p1.fragments_.first, p2.fragments_.first), overlap(p1.fragments_.second, p2.fragments_.second));
}

float ok(const clone_pair &p1, const clone_pair &p2) noexcept
{
	return std::min(
		std::max(contained(p1.fragments_.first, p2.fragments_.first), contained(p2.fragments_.first, p1.fragments_.first)),
		std::max(contained(p1.fragments_.second, p2.fragments_.second), contained(p2.fragments_.second, p1.fragments_.second))
	);
}

};
