#include "clone_io.hpp"


namespace asterism
{


clone_io::clone_io()
{

}


std::optional<detection_results> clone_io::read(const QString &file) noexcept
{
	if(auto info=QFileInfo(file); info.suffix()=="jcln")
	{
		return jcln::read(file, false);
	}
	else if(info.suffix()=="bjcln")
	{
		return jcln::read(file, true);
	}

	return std::nullopt;
}


}
