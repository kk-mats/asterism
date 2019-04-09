#include "clone_io.hpp"


namespace asterism
{


clone_io::clone_io()
{

}


std::optional<detection_results> clone_io::read_jcln(const QString &file, const bool is_binary) noexcept
{
	return jcln::read(file, is_binary);
}


}
