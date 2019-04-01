#ifndef OBJECT_ID_T_HPP
#define OBJECT_ID_T_HPP

#include <cstdint>

namespace asterism
{

template <class N>
class object_id_t final
{
public:
	object_id_t(const uint32_t id) noexcept
		: id_(id)
	{}

	uint32_t id() const noexcept
	{
		return this->id_;
	}

	object_id_t<N>& operator ++() noexcept
	{
		++this->id_;
		return *this;
	}

	object_id_t<N>& operator --() noexcept
	{
		--this->id_;
		return *this;
	}

	object_id_t<N> operator ++(int) noexcept
	{
		auto t=*this;
		++(*this);
		return t;
	}

	object_id_t<N> operator --(int) noexcept
	{
		auto t=*this;
		--(*this);
		return t;
	}

	bool operator ==(const object_id_t<N> &other) const noexcept
	{
		return this->id_==other.id_;
	}

	bool operator !=(const object_id_t<N> &other) const noexcept
	{
		return !(*this==other);
	}

	bool operator <(const object_id_t<N> &other) const noexcept
	{
		return this->id_<other.id_;
	}

	operator int() const noexcept
	{
		return int(this->id_);
	}

private:
	uint32_t id_;
};

}

#endif // OBJECT_ID_T_HPP
