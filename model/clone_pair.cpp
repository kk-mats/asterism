#include "clone_pair.hpp"

namespace asterism
{

// constructor
clone_pair::clone_pair(const fragment &fragment1, const fragment &fragment2, const unsigned int similarity) noexcept
	: id_(new_id()), fragments_(canonical(fragment1, fragment2)), similairty_(similarity)
{}

clone_pair::clone_pair(fragment &&fragment1, fragment &&fragment2, const unsigned int similarity) noexcept
	: id_(new_id()), fragments_(canonical(fragment1, fragment2)), similairty_(similarity)
{}


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

};
