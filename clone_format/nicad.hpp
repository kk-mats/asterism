#ifndef NICAD_HPP
#define NICAD_HPP

#include <QXmlStreamReader>

#include <functional>

#include "format_tags.hpp"
#include "core/logger.hpp"
#include "core/detection_results.hpp"

namespace asterism
{

class nicad final
	: public format_tags
{
public:
	static std::shared_ptr<detection_result> read(const QString &path, detection_results &results) noexcept;

private:
	class reader final
	{
	public:
		reader(QFile &file, detection_results &results) noexcept;
		std::shared_ptr<detection_result> read() noexcept;

	private:
		QXmlStreamReader is_;
		detection_results &results_;

		std::optional<result_environment> read_environment() noexcept;
		std::optional<std::shared_ptr<clone_pair>> read_clone() noexcept;
		std::optional<fragment> read_fragment() noexcept;
	};
};

}

#endif // NICAD_HPP