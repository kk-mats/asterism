#ifndef OBJECT_ID_T_HPP
#define OBJECT_ID_T_HPP

#include <cstdint>

namespace asterism
{

template <class N>
class object_id_t
{
public:
	object_id_t(const uint32_t index) noexcept
		: index_(index)
	{}

	uint32_t index() const noexcept
	{
		return this->index_;
	}

	bool operator ==(const object_id_t<N> &other) const noexcept
	{
		return this->index_==other.index_;
	}

	bool operator !=(const object_id_t<N> &other) const noexcept
	{
		return !(*this==other);
	}

	bool operator <(const object_id_t<N> &other) const noexcept
	{
		return this->index_<other.index_;
	}

private:
	const uint32_t index_;
};

}

#endif // OBJECT_ID_T_HPP
