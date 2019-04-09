#ifndef CLONE_IO_HPP
#define CLONE_IO_HPP

#include "jcln.hpp"

namespace asterism
{

class clone_io
{
public:
	clone_io();

	static std::optional<detection_results> read_jcln(const QString &file, const bool is_binary) noexcept;
};

}

#endif // CLONE_IO_HPP
