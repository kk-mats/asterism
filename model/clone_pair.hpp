#ifndef CLONE_PAIR_HPP
#define CLONE_PAIR_HPP

#include "fragment.hpp"

namespace asterism
{

class clone_pair
{
public:
	using id_t=object_id_t<clone_pair>;

	clone_pair(const fragment &fragment1, const fragment &fragment2, const unsigned int similarity) noexcept;
	clone_pair(fragment &&fragment1, fragment &&fragment2, const unsigned int similarity) noexcept;

	bool operator <(const clone_pair &other) const noexcept;

	id_t id() const noexcept;
	fragment fragment1() const noexcept;
	fragment fragment2() const noexcept;
	unsigned int similarity() const noexcept;

	QJsonValue to_qjson() const noexcept;
private:
	id_t id_;
	std::pair<fragment, fragment> fragments_;
	unsigned int similairty_;

	static uint32_t id_ctr_;
	static id_t new_id() noexcept;

	std::pair<fragment, fragment> normalize(const fragment &fragment1, const fragment &fragment2) noexcept;
	std::pair<fragment, fragment> normalize(fragment &&fragment1, fragment &&fragment2) noexcept;
};

using clone_pair_id_t=object_id_t<clone_pair>;
}

#endif // CLONE_PAIR_HPP
