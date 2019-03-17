#include "jcln.hpp"

namespace asterism
{


std::optional<detection_results> jcln::parse(const QString &path) noexcept
{
	QFile file(path);

	if(QFile file(path); !file.open(QIODevice::ReadOnly))
	{
		return std::nullopt;
	}

	auto json(QFileInfo(path).suffix()=="jcln" ?
				QJsonDocument::fromJson(file.readAll()) : // file.jcln
				QJsonDocument::fromBinaryData(file.readAll())); //file.bjcln

	if(!json.isObject())
	{
		return std::nullopt;
	}

	auto j=json.object();

	if(j.contains("global") && )


}


QJsonValue jcln::to_qjson(const file &file) noexcept
{
	return QJsonObject
	{
		{"file_id", int(file.id())},
		{"path", file.canonical_file_path()}
	};
}

QJsonValue jcln::to_qjson(const fragment &fragment) noexcept
{
	return QJsonObject
	{
		{"file_id", int(fragment.file_id())},
		{"begin", int(fragment.begin())},
		{"end", int(fragment.end())}
	};
}

QJsonValue jcln::to_qjson(const clone_pair &clone_pair) noexcept
{
	return QJsonObject
	{
		{"clone_pair_id", int(clone_pair.id())},
		{"similarity", int(clone_pair.similarity())},
		{"fragment1", to_qjson(clone_pair.fragment1())},
		{"fragment2", to_qjson(clone_pair.fragment2())}
	};
}

QJsonValue jcln::to_qjson(const detection_result &detection_result) noexcept
{
	QJsonArray json_clone_pairs_array;
	for(const auto &p:detection_result.clone_pair_table())
	{
		json_clone_pairs_array.append(to_qjson(p));
	}

	return QJsonObject
	{
		{"result_id", int(detection_result.id())},
		{"clone_pairs", json_clone_pairs_array}
	};
}

QJsonValue jcln::to_qjson(const detection_results &detection_results) noexcept
{
	QJsonArray files, results;
	for(const auto &f:detection_results.file_table())
	{
		files.append(to_qjson(f));
	}

	for(const auto &r:detection_results.result_table())
	{
		results.append(to_qjson(r));
	}

	return QJsonObject
	{
		{"global",
			{"target", 			}
		}
	};
}

std::optional<fragment> jcln::read_fragment(const QJsonObject &json) noexcept
{
	if(!json.contains(FILE_ID) || !json.contains(BEGIN) || !json.contains(END))
	{
		return std::nullopt;
	}

	if(!json[FILE_ID].isDouble() || !json[BEGIN].isDouble() || !json[END].isDouble())
	{
		return std::nullopt;
	}

	return fragment(file::id_t(json[FILE_ID].toInt()), json[BEGIN].toInt(), json[END].toInt());
}

std::optional<clone_pair> jcln::read_clone_pair(const QJsonObject &json) noexcept
{
	if(!json.contains(SIMILARITY) || !json.contains(FRAGMENT1) || !json.contains(FRAGMENT2))
	{
		return std::nullopt;
	}

	if(!json[SIMILARITY].isDouble() || !json[FRAGMENT1].isObject() || !json[FRAGMENT2].isObject())
	{
		return std::nullopt;
	}

	auto f1=read_fragment(json[FRAGMENT1].toObject());
	auto f2=read_fragment(json[FRAGMENT2].toObject());

	return f1 && f2 ? std::make_optional(clone_pair(std::move(f1.value()), std::move(f2.value()), json[SIMILARITY].toInt())) : std::nullopt;
}


std::optional<detection_result> jcln::read_detection_result(const QJsonObject &json) noexcept
{
	if(!json.contains(ENVIRONMENT) || !json.contains(RESULT_ID) || !json.contains(CLONE_PAIRS))
	{
		return std::nullopt;
	}

	if(!json[ENVIRONMENT].isObject() || !json[RESULT_ID].isDouble() || !json[CLONE_PAIRS].isArray())
	{
		return std::nullopt;
	}

	// environment
	const auto environment=json[ENVIRONMENT].toObject();
	if(!environment.contains(SOURCE) || !environment.contains(CLONE_DETECTOR))
	{
		return std::nullopt;
	}

	if(!environment[SOURCE].isString() || !environment[CLONE_DETECTOR].isObject())
	{
		return std::nullopt;
	}

	// environment.clone_detector
	const auto clone_detector=environment[CLONE_DETECTOR].toObject();
	if(!clone_detector.contains(NAME) || !clone_detector[NAME].isString())
	{
		return std::nullopt;
	}

	auto context=result_context(clone_detector[NAME].toString(), environment[SOURCE].toString());

	QHash<clone_pair::id_t, clone_pair> clone_pair_table;
	for(const auto &pj:json[CLONE_PAIRS].toArray())
	{
		std::optional<clone_pair> p;
		if(!pj.isObject() || !(p=read_clone_pair(pj.toObject())))
		{
			return std::nullopt;
		}

		clone_pair_table[p.value().id()]=std::move(p.value());
	}

	return detection_result(json[RESULT_ID].toInt(), std::move(context), std::move(clone_pair_table));
}

std::optional<detection_results> jcln::read_detection_results(const QJsonObject &json) noexcept
{
	if(!json.contains(GLOBAL) || !json.contains(FILE_TABLE) || !json.contains(RESULTS))
	{
		return std::nullopt;
	}

	if(!json[GLOBAL].isObject() || !json[FILE_TABLE].isArray() || !json[RESULTS].isArray())
	{
		return std::nullopt;
	}

	// global
	const auto global=json[GLOBAL].toObject();
	if(!global.contains(TARGET) || !global[TARGET].isString())
	{
		return std::nullopt;
	}

	detection_results rs(global[TARGET].toString());

	// file_table
	const auto file_table=json[FILE_TABLE].toArray();
	for(const auto &fj:file_table)
	{
		if(!fj.isObject())
		{
			return std::nullopt;
		}

		auto f=fj.toObject();
		if(!f.contains(FILE_ID) || !f.contains(PATH) || !f[FILE_ID].isDouble() || f[PATH].isString())
		{
			return std::nullopt;
		}

		rs.add(file(f[FILE_ID].toInt(), to_canonical_file_path(f[PATH].toString())));
	}

	// results
	const auto results=json[RESULTS].toArray();
	for(const auto &rj:results)
	{
		if(!rj.isObject())
		{
			return std::nullopt;
		}

		auto r=read_detection_result(rj.toObject());
		if(!r)
		{
			return std::nullopt;
		}

		rs.add(std::move(r.value()));
	}

	return std::move(rs);
}

}
