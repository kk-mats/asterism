#include "fragment.hpp"


namespace asterism
{
// constructor, destructor
fragment::fragment() noexcept
	: file_(nullptr), begin_(0), end_(0)
{}

fragment::fragment(const std::shared_ptr<file> &file, const uint32_t begin, const uint32_t end) noexcept
	:file_(file), begin_(begin), end_(end)
{}

// operator
bool fragment::operator <(const fragment &other) const noexcept
{
	if(this->file_<other.file_)
	{
		return true;
	}

	if(this->file_==other.file_)
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

uint32_t fragment::operator &(const fragment &other) const noexcept
{
	return std::min(this->end_, other.end_)-std::max(this->begin_, other.begin_);
}

uint32_t fragment::operator |(const fragment &other) const noexcept
{
	return std::max(this->end_, other.end_)-std::min(this->begin_, other.begin_);
}

std::weak_ptr<file> fragment::file_ptr() const noexcept
{
	return this->file_;
}

uint32_t fragment::begin() const noexcept
{
	return this->begin_;
}

uint32_t fragment::end() const noexcept
{
	return this->end_;
}

float overlap(const fragment &f1, const fragment &f2) noexcept
{
	return float(f1&f2)/(f1|f2);
}

float contained(const fragment &f1, const fragment &f2) noexcept
{
	return float(f1&f2)/(f1.end_-f1.begin_);
}

QDebug operator <<(QDebug logger, const fragment &fragment) noexcept
{
	logger<<"id="<<std::intptr_t(fragment.file_ptr().lock().get())<<"["<<fragment.begin_<<", "<<fragment.end_<<"]";
	return logger;
}

}
