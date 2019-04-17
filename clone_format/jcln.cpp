#include "jcln.hpp"

namespace asterism
{


std::optional<detection_results> jcln::read(const QString &path) noexcept
{
	QFile file(path);

	if(!file.open(QIODevice::ReadOnly))
	{
		qCritical()<<code_clone_loading_error::file_not_found<<path;
		return std::nullopt;
	}

	auto json(QFileInfo(file).suffix()=="jcln" ?
				QJsonDocument::fromJson(file.readAll()) : // *.jcln
				QJsonDocument::fromBinaryData(file.readAll())); // *.bjcln

	if(!json.isObject())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	return reader().read(json.object());
}


bool jcln::write(const detection_results &results, const QString &path) noexcept
{
	QFile file(path);

	if(!file.open(QIODevice::WriteOnly))
	{
		qCritical()<<code_clone_loading_error::file_not_found<<path;
		return false;
	}

	file.write(QJsonDocument(writer().to_qjson(results).toObject()).toJson());
	qInfo()<<"write to "<<path;
	return true;
}


QJsonValue jcln::writer::to_qjson(const std::weak_ptr<file> &file_ptr, const file_index &file_index) noexcept
{
	return QJsonObject
	{
		{FILE_ID, file_index[file_ptr]},
		{PATH, file_ptr.lock()->canonical_file_path()}
	};
}

QJsonValue jcln::writer::to_qjson(const fragment &fragment, const file_index &file_index) noexcept
{
	return QJsonObject
	{
		{FILE_ID, int(file_index[fragment.file_ptr()])},
		{BEGIN, int(fragment.begin())},
		{END, int(fragment.end())}
	};
}

QJsonValue jcln::writer::to_qjson(const std::shared_ptr<clone_pair> &clone_pair, const file_index &file_index) noexcept
{
	return QJsonObject
	{
		{SIMILARITY, int(clone_pair->similarity())},
		{FRAGMENT1, to_qjson(clone_pair->fragment1(), file_index)},
		{FRAGMENT2, to_qjson(clone_pair->fragment2(), file_index)}
	};
}

QJsonValue jcln::writer::to_qjson(const std::shared_ptr<detection_result> &detection_result, const file_index &file_index) noexcept
{
	QJsonArray json_clone_pairs_array;
	for(const auto &p:detection_result->clone_pairs())
	{
		json_clone_pairs_array.append(to_qjson(p, file_index));
	}

	QJsonObject json_parameters;
	const auto parameters=detection_result->environment().parameters();
	for(const auto &k:parameters.keys())
	{
		json_parameters[k]=parameters[k];
	}

	return QJsonObject
	{
		{ENVIRONMENT, QJsonObject{
			{SOURCE, detection_result->environment().source()},
			{PARAMETERS, json_parameters}
		}},
		{CLONE_PAIR_SIZE, detection_result->clone_pairs().size()},
		{CLONE_PAIRS, json_clone_pairs_array}
	};
}

QJsonValue jcln::writer::to_qjson(const detection_results &detection_results) noexcept
{
	QJsonArray files, results;
	const auto &file_index=detection_results.file_index_map();
	for(const auto &f:detection_results.files())
	{
		files.append(to_qjson(f, file_index));
	}

	for(const auto &r:detection_results.results())
	{
		results.append(to_qjson(r, file_index));
	}

	return QJsonObject
	{
		{GLOBAL, QJsonObject{
			{TARGET, detection_results.target_path()}}
		},
		{FILE_TABLE, files},
		{RESULTS, results}
	};
}

std::optional<fragment> jcln::reader::read_fragment(const QJsonObject &json) noexcept
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

std::optional<clone_pair> jcln::reader::read_clone_pair(const QJsonObject &json) noexcept
{
	if(!json.contains(SIMILARITY) || !json.contains(FRAGMENT1) || !json.contains(FRAGMENT2))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	if(!json[SIMILARITY].isDouble() || !json[FRAGMENT1].isObject() || !json[FRAGMENT2].isObject())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	auto f1=this->read_fragment(json[FRAGMENT1].toObject());
	auto f2=this->read_fragment(json[FRAGMENT2].toObject());

	return f1 && f2 ? std::make_optional<clone_pair>(std::move(f1.value()), std::move(f2.value()), json[SIMILARITY].toInt()) : std::nullopt;
}


bool jcln::reader::read_detection_result(const QJsonObject &json) noexcept
{
	if(!json.contains(ENVIRONMENT) || !json.contains(CLONE_PAIRS))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return false;
	}

	if(!json[ENVIRONMENT].isObject() || !json[CLONE_PAIRS].isArray())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return false;
	}

	// environment
	const auto environment=json[ENVIRONMENT].toObject();
	if(!environment.contains(SOURCE) || !environment.contains(CLONE_DETECTOR))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return false;
	}

	if(!environment[SOURCE].isString() || !environment[CLONE_DETECTOR].isObject())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return false;
	}

	// environment.clone_detector
	const auto clone_detector=environment[CLONE_DETECTOR].toObject();
	if(!clone_detector.contains(NAME) || !clone_detector[NAME].isString())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return false;
	}

	shared_set<clone_pair> clone_pairs;
	for(auto pj:json[CLONE_PAIRS].toArray())
	{
		std::optional<clone_pair> p;
		if(!pj.isObject() || !(p=read_clone_pair(pj.toObject())))
		{
			qCritical()<<code_clone_loading_error::invalid_file_format;
			return false;
		}

		clone_pairs.insert(std::make_shared<clone_pair>(std::move(p.value())));
	}

	this->results_.empalce(result_environment(clone_detector[NAME].toString(), environment[SOURCE].toString()), std::move(clone_pairs));
	return true;
}

std::optional<detection_results> jcln::reader::read(const QJsonObject &json) noexcept
{
	if(!json.contains(GLOBAL) || !json.contains(FILE_TABLE) || !json.contains(RESULTS))
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	if(!json[GLOBAL].isObject() || !json[FILE_TABLE].isArray() || !json[RESULTS].isArray())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	// global
	const auto global=json[GLOBAL].toObject();
	if(!global.contains(TARGET) || !global[TARGET].isString())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	this->results_.set_target_path(global[TARGET].toString());

	// file_table
	for(const auto fj:json[FILE_TABLE].toArray())
	{
		if(!fj.isObject())
		{
			qCritical()<<code_clone_loading_error::invalid_file_format;
			return std::nullopt;
		}

		auto f=fj.toObject();
		if(!f.contains(FILE_ID) || !f.contains(PATH) || !f[FILE_ID].isDouble() || !f[PATH].isString())
		{
			qCritical()<<code_clone_loading_error::invalid_file_format;
			return std::nullopt;
		}

		auto filepath=to_canonical_file_path(f[PATH].toString());
		if(filepath.isEmpty())
		{
			qCritical()<<code_clone_loading_error::file_not_found;
			return std::nullopt;
		}
		this->id_file_ptr_map_[f[FILE_ID].toInt()]=this->results_.emplace(std::move(filepath));
	}

	// results
	for(const auto rj:json[RESULTS].toArray())
	{
		if(!rj.isObject() || !this->read_detection_result(rj.toObject()))
		{
			qCritical()<<code_clone_loading_error::invalid_file_format;
			return std::nullopt;
		}
	}

	return this->results_;
}

}
