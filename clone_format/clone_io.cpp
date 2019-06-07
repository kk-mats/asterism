#include "clone_io.hpp"


namespace asterism
{


clone_io::clone_io()
{

}


std::optional<detection_results> clone_io::read_jcln(const QString &file) noexcept
{
	return jcln::read(file);
}

std::shared_ptr<detection_result> clone_io::read_ccfinderx(const QString &file, detection_results &results) noexcept
{
	return ccfinderx::read(file, results);
}

std::shared_ptr<detection_result> clone_io::read_ccfindersw(const QString &file, detection_results &results) noexcept
{
	return ccfindersw::read(file, results);
}

std::shared_ptr<detection_result> clone_io::read_nicad(const QString &file, detection_results &results) noexcept
{
	return nicad::read(file, results);
}

bool clone_io::write_csv(const QString &file, const detection_result &result, const QString &project_root) noexcept
{
	return csv::write(result, project_root, file);
}


}
