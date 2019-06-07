#ifndef CCFINDERX_HPP
#define CCFINDERX_HPP

#include <QByteArray>
#include <QFile>
#include <QDataStream>

#include "core/logger.hpp"
#include "core/global_settings.hpp"
#include "core/detection_results.hpp"

namespace asterism
{

class ccfinderx final
{
public:
	static std::shared_ptr<detection_result> read(const QString &path, detection_results &results) noexcept;

	static inline const QString magic_number="ccfxraw0";

private:
	class reader final
	{
	public:
		reader(QFile &file) noexcept;
		std::shared_ptr<detection_result> read(detection_results &results) noexcept;

	private:
		QDataStream is_;
		bool check_version() noexcept;
	};

};

}

#endif // CCFINDERX_HPP