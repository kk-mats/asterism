#include "fragment.hpp"


namespace asterism
{
// constructor, destructor
fragment::fragment() noexcept
	: file_id_(0), begin_(0), end_(0)
{}

fragment::fragment(const file::id_t &file_id, const uint32_t begin, const uint32_t end) noexcept
	:file_id_(file_id), begin_(begin), end_(end)
{}

// operator
bool fragment::operator <(const fragment &other) const noexcept
{
	if(this->file_id_<other.file_id_)
	{
		return true;
	}

	if(this->file_id_==other.file_id_)
	{
		if(this->begin_<other.begin_)
		{
			return true;
		}

		if(this->begin_==other.begin_ && this->end_<other.end_)
		{
			return true;
		}
	}

	return false;
}


file::id_t fragment::file_id() const noexcept
{
	return this->file_id_;
}

uint32_t fragment::begin() const noexcept
{
	return this->begin_;
}

uint32_t fragment::end() const noexcept
{
	return this->end_;
}

}
