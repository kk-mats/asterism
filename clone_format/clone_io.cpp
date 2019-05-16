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

std::shared_ptr<detection_result> clone_io::read_json(const QString &file, detection_results &results) noexcept
{
	return json::read(file, results);
}

bool clone_io::write_csv(const QString &file, const detection_result &result, const QString &project_root) noexcept
{
	return csv::write(result, project_root, file);
}


}
