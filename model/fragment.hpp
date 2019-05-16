#ifndef FRAGMENT_HPP
#define FRAGMENT_HPP

#include <memory>

#include "file.hpp"

namespace asterism
{

class fragment final
{
public:
	fragment() noexcept;
	fragment(const std::shared_ptr<file> &file, const uint32_t begin, const uint32_t end) noexcept;

	bool is_overlapped(const fragment &other) const noexcept;
	QString string() const noexcept;

	std::shared_ptr<file> file_ptr() const noexcept;
	uint32_t begin() const noexcept;
	uint32_t end() const noexcept;
	int length() const noexcept;
		
	bool operator ==(const fragment &other) const noexcept;
	bool operator <(const fragment &other) const noexcept;
	uint32_t operator &(const fragment &other) const noexcept;
	uint32_t operator |(const fragment &other) const noexcept;

	friend QDebug operator <<(QDebug logger, const fragment &fragment) noexcept;

	friend float overlap(const fragment &f1, const fragment &f2) noexcept;
	friend float contained(const fragment &f1, const fragment &f2) noexcept;

private:
	std::shared_ptr<file> file_;
	uint32_t begin_, end_;
};

float overlap(const fragment &f1, const fragment &f2) noexcept;
float contained(const fragment &f1, const fragment &f2) noexcept;

QDebug operator <<(QDebug logger, const fragment &fragment) noexcept;

Q_DECLARE_METATYPE(fragment)
}

#endif // FRAGMENT_HPP
