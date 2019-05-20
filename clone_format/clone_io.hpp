#ifndef CLONE_IO_HPP
#define CLONE_IO_HPP

#include "jcln.hpp"
#include "json.hpp"
#include "csv.hpp"
#include "nicad.hpp"

namespace asterism
{

class clone_io
{
public:
	clone_io();

	static std::optional<detection_results> read_jcln(const QString &file) noexcept;
	static std::shared_ptr<detection_result> read_json(const QString &file, detection_results &results) noexcept;
	static std::shared_ptr<detection_result> read_nicad(const QString &file, detection_results &results) noexcept;

	static bool write_csv(const QString &file, const detection_result &result, const QString &project_root) noexcept;
};

}

#endif // CLONE_IO_HPP
