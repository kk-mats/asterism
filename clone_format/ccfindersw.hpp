#ifndef CCFINDERSW_HPP
#define CCFINDERSW_HPP

#include <QJsonDocument>

#include "format_tags.hpp"
#include "core/logger.hpp"
#include "core/detection_results.hpp"

namespace asterism
{

class ccfindersw final
	: public format_tags
{
public:
	static std::shared_ptr<detection_result> read(const QString &path, detection_results &results) noexcept;

private:
	class reader final
	{
	public:
		reader()=default;
		std::shared_ptr<detection_result> read(const QString &path, const QJsonObject &json, detection_results &results) noexcept;

	private:
		std::optional<fragment> read_fragment(const QJsonObject &json) noexcept;
		bool read_clone_pair(const QJsonObject &json, shared_set<clone_pair> &clone_pairs) noexcept;

		shared_map<int, file> id_file_ptr_map_;
	};

};

}

#endif // CCFINDERSW_HPP
