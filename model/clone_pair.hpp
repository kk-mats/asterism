#ifndef CLONE_PAIR_HPP
#define CLONE_PAIR_HPP

#include "fragment.hpp"

namespace asterism
{

class clone_pair final
{
public:
	using id_t=object_id_t<clone_pair>;

	clone_pair() noexcept;
	clone_pair(const fragment &fragment1, const fragment &fragment2, const unsigned int similarity) noexcept;
	clone_pair(fragment &&fragment1, fragment &&fragment2, const unsigned int similarity) noexcept;

	bool operator ==(const clone_pair &other) const noexcept;
	bool operator <(const clone_pair &other) const noexcept;

	id_t id() const noexcept;
	fragment fragment1() const noexcept;
	fragment fragment2() const noexcept;
	unsigned int similarity() const noexcept;

	friend float good(const clone_pair &p1, const clone_pair &p2) noexcept;
	friend float ok(const clone_pair &p1, const clone_pair &p2) noexcept;

private:
	id_t id_;
	QPair<fragment, fragment> fragments_;
	unsigned int similairty_;

	static inline uint32_t id_ctr_=0;
	static id_t new_id() noexcept;

	QPair<fragment, fragment> canonical(const fragment &fragment1, const fragment &fragment2) noexcept;
	QPair<fragment, fragment> canonical(fragment &&fragment1, fragment &&fragment2) noexcept;
};

uint qHash(const clone_pair::id_t &key, uint seed) noexcept;
uint qHash(const clone_pair &key, uint seed) noexcept;

float good(const clone_pair &p1, const clone_pair &p2) noexcept;
float ok(const clone_pair &p1, const clone_pair &p2) noexcept;

}

#endif // CLONE_PAIR_HPP
