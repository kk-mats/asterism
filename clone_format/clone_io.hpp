#ifndef CLONE_IO_HPP
#define CLONE_IO_HPP

#include "jcln.hpp"
#include "csv.hpp"
#include "nicad.hpp"
#include "ccfinderx.hpp"
#include "ccfindersw.hpp"
#include "ccvolti.hpp"

namespace asterism
{

class clone_io final
{
public:
	clone_io();

	static std::optional<detection_results> read_jcln(const QString &file) noexcept;
	static std::shared_ptr<detection_result> read_ccfinderx(const QString &file, detection_results &results) noexcept;
	static std::shared_ptr<detection_result> read_ccvolti(const QString &file, detection_results &results) noexcept;
	static std::shared_ptr<detection_result> read_ccfindersw(const QString &file, detection_results &results) noexcept;
	static std::shared_ptr<detection_result> read_nicad(const QString &file, detection_results &results) noexcept;

	static bool write_jcln(const QString &file, const detection_results &results) noexcept;
	static bool write_csv(const QString &file, const detection_result &result, const QString &project_root) noexcept;
};

}

#endif // CLONE_IO_HPP
