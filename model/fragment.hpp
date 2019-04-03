#ifndef FRAGMENT_HPP
#define FRAGMENT_HPP

#include "file.hpp"

namespace asterism
{

class fragment final
{
public:
	fragment() noexcept;
	fragment(const file::id_t &file_id, const uint32_t begin, const uint32_t end) noexcept;

	bool operator <(const fragment &other) const noexcept;
	uint32_t operator &(const fragment &other) const noexcept;
	uint32_t operator |(const fragment &other) const noexcept;

	file::id_t file_id() const noexcept;
	uint32_t begin() const noexcept;
	uint32_t end() const noexcept;

	friend float overlap(const fragment &f1, const fragment &f2) noexcept;
	friend float contained(const fragment &f1, const fragment &f2) noexcept;

private:
	file::id_t file_id_;
	uint32_t begin_, end_;
};

float overlap(const fragment &f1, const fragment &f2) noexcept;
float contained(const fragment &f1, const fragment &f2) noexcept;

}

#endif // FRAGMENT_HPP
