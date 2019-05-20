#include "json.hpp"

namespace asterism
{

std::shared_ptr<detection_result> json::read(const QString &path, detection_results &results) noexcept
{
	QFile file(path);

	if(!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		qCritical()<<code_clone_loading_error::file_not_found<<path;
		return nullptr;
	}

	auto jj(QJsonDocument::fromJson(file.readAll()));

	if(!jj.isObject())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	return reader().read(path, jj.object(), results);
}

std::shared_ptr<detection_result> json::reader::read(const QString &path, const QJsonObject &json, detection_results &results) noexcept
{
	if(!json.contains(ENVIRONMENT) || !json.contains(FILE_TABLE) || !json.contains(CLONE_PAIRS))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	if(!json[ENVIRONMENT].isObject() || !json[FILE_TABLE].isArray() || !json[CLONE_PAIRS].isArray())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	// environment
	const auto environment=json[ENVIRONMENT].toObject();
	if(!environment.contains(TARGET) || !environment.contains(CLONE_DETECTOR))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}
	
	if(!environment[TARGET].isObject() || !environment[CLONE_DETECTOR].isObject())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	const auto target=environment[TARGET].toObject();
	const auto clone_detector=environment[CLONE_DETECTOR].toObject();

	if(!target.contains(PROJECT_ROOT) || !target[PROJECT_ROOT].isString())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	if(!clone_detector.contains(NAME) || !clone_detector[NAME].isString())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	result_environment re(clone_detector[NAME].toString(), path);
	

	// file_table
	for(const auto fj:json[FILE_TABLE].toArray())
	{
		if(!fj.isObject())
		{
			qCritical()<<code_clone_loading_error::invalid_file_format;
			return nullptr;
		}

		auto f=fj.toObject();
		if(!f.contains(FILE_ID) || !f.contains(PATH) || !f[FILE_ID].isDouble() || !f[PATH].isString())
		{
			qCritical()<<code_clone_loading_error::invalid_file_format;
			return nullptr;
		}

		auto filepath=to_canonical_file_path(f[PATH].toString());
		if(filepath.isEmpty())
		{
			qCritical()<<code_clone_loading_error::file_not_found;
			return nullptr;
		}
		this->id_file_ptr_map_[f[FILE_ID].toInt()]=results.emplace(std::move(filepath));
	}

	// clone_pairs
	shared_set<clone_pair> clone_pairs;
	for(const auto p:json[CLONE_PAIRS].toArray())
	{
		if(!p.isObject() || !this->read_clone_pair(p.toObject(), clone_pairs))
		{
			qCritical()<<code_clone_loading_error::file_not_found;
			return nullptr;
		}
	}

	return results.empalce(std::move(re), std::move(clone_pairs));
}

std::optional<fragment> json::reader::read_fragment(const QJsonObject &json) noexcept
{
	if(!json.contains(FILE_ID) || !json.contains(BEGIN) || !json.contains(END))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	if(!json[FILE_ID].isDouble() || !json[BEGIN].isDouble() || !json[END].isDouble())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	auto file_id=json[FILE_ID].toInt();
	if(!this->id_file_ptr_map_.contains(file_id))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	return fragment(this->id_file_ptr_map_[file_id], json[BEGIN].toInt(), json[END].toInt());
}

bool json::reader::read_clone_pair(const QJsonObject &json, shared_set<clone_pair> &clone_pairs) noexcept
{
	if(!json.contains(SIMILARITY) || !json.contains(FRAGMENT1) || !json.contains(FRAGMENT2))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return false;
	}

	if(!json[SIMILARITY].isDouble() || !json[FRAGMENT1].isObject() || !json[FRAGMENT2].isObject())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return false;
	}

	auto f1=this->read_fragment(json[FRAGMENT1].toObject());
	auto f2=this->read_fragment(json[FRAGMENT2].toObject());

	if(f1 && f2)
	{
		clone_pairs.insert(std::make_shared<clone_pair>(std::move(f1.value()), std::move(f2.value()), json[SIMILARITY].toInt()));
		return true;
	}

	return false;
}

}