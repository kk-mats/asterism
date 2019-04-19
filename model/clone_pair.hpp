#ifndef CLONE_PAIR_HPP
#define CLONE_PAIR_HPP

#include "fragment.hpp"

namespace asterism
{

class clone_pair final
{
public:
	clone_pair() noexcept;
	clone_pair(const fragment &fragment1, const fragment &fragment2, const unsigned int similarity) noexcept;
	clone_pair(fragment &&fragment1, fragment &&fragment2, const unsigned int similarity) noexcept;

	bool operator ==(const clone_pair &other) const noexcept;
	bool operator <(const clone_pair &other) const noexcept;

	fragment fragment1() const noexcept;
	fragment fragment2() const noexcept;
	unsigned int similarity() const noexcept;

	friend uint qHash(const clone_pair &key, uint seed) noexcept;
	friend QDebug operator <<(QDebug logger, const clone_pair &clone_pair) noexcept;

	friend float good(const clone_pair &p1, const clone_pair &p2) noexcept;
	friend float ok(const clone_pair &p1, const clone_pair &p2) noexcept;

private:
	std::pair<fragment, fragment> fragments_;
	unsigned int similairty_;
};

uint qHash(const clone_pair &key, uint seed) noexcept;
QDebug operator <<(QDebug logger, const clone_pair &clone_pair) noexcept;

float good(const clone_pair &p1, const clone_pair &p2) noexcept;
float ok(const clone_pair &p1, const clone_pair &p2) noexcept;

}

#endif // CLONE_PAIR_HPP
