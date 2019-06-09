#include "nicad.hpp"

namespace asterism
{

std::shared_ptr<detection_result> nicad::read(const QString &path, detection_results &results) noexcept
{
	QFile file(path);

	if(!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		qCritical()<<code_clone_loading_error::file_not_found<<path;
		return nullptr;
	}

	return reader(file, results).read();
}

nicad::reader::reader(QFile &file, detection_results &results) noexcept
	: is_(&file), results_(results)
{}

std::shared_ptr<detection_result> nicad::reader::read() noexcept
{
	std::optional<result_environment> environment=std::nullopt;
	shared_set<clone_pair> clone_pairs;

	// QXmlReader::atEnd() returns false when an error occurred
	while(!this->is_.atEnd() && this->is_.readNext())
	{
		if(this->is_.isStartElement())
		{
			const auto name=this->is_.name();
			if(name==CLONE)
			{
				auto p=this->read_clone();
				if(!p)
				{
					break;
				}
				clone_pairs.insert(p.value());
			}
			else if(name==SYSTEMINFO && !(environment=this->read_environment()))
			{
				break;
			}
		}
	}

	if(!this->is_.atEnd())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	return this->results_.empalce(std::move(environment.value()), std::move(clone_pairs));
}

std::optional<result_environment> nicad::reader::read_environment() noexcept
{
	const auto attributes=this->is_.attributes();

	if(!attributes.hasAttribute(PROCESSOR) || attributes.value(PROCESSOR)!="nicad5")
	{
		return std::nullopt;
	}

	result_environment environment(clone_detector_t::nicad, static_cast<QFile*>(this->is_.device())->fileName());
	for(const auto &attribute:attributes)
	{
		if(attribute.name()!=PROCESSOR)
		{
			environment.add_parameter(attribute.name().toString(), attribute.value().toString());
		}
	}

	return std::make_optional(environment);
}

std::optional<std::shared_ptr<clone_pair>> nicad::reader::read_clone() noexcept
{
	const auto attributes=this->is_.attributes();
	if(!attributes.hasAttribute(SIMILARITY))
	{
		return std::nullopt;
	}

	bool ok=false;
	const auto similarity=attributes.value(SIMILARITY).toInt(&ok);
	if(!ok)
	{
		return std::nullopt;
	}

	if(!this->is_.readNextStartElement())
	{
		return std::nullopt;
	}
	const auto f1=this->read_fragment();

	if(this->is_.readNext()!=QXmlStreamReader::TokenType::EndElement || !this->is_.readNextStartElement())
	{
		return std::nullopt;
	}
	const auto f2=this->read_fragment();

	return std::make_shared<clone_pair>(f1.value(), f2.value(), similarity);
}

std::optional<fragment> nicad::reader::read_fragment() noexcept
{
	const auto attributes=this->is_.attributes();
	if(!attributes.hasAttribute(FILE) || !attributes.hasAttribute(STARTLINE) || !attributes.hasAttribute(ENDLINE))
	{
		return std::nullopt;
	}

	bool ok1=false, ok2=false;
	const auto startline=attributes.value(STARTLINE).toInt(&ok1);
	const auto endline=attributes.value(ENDLINE).toInt(&ok2);

	if(!ok1 || !ok2)
	{
		return std::nullopt;
	}

	return std::make_optional<fragment>(this->results_.emplace(attributes.value(FILE).toString()), startline, endline);
}

}