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

	QDomElement root;
	if(QDomDocument xx; !xx.setContent(&file) || (root=xx.documentElement()).tagName()!=CLONES)
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	return reader(path, results).read(root);
}

nicad::reader::reader(const QString &path, detection_results &results) noexcept
	: source_(path), results_(results)
{}

std::shared_ptr<detection_result> nicad::reader::read(const QDomElement &root) noexcept
{
	const auto envs=root.elementsByTagName(SYSTEMINFO);
	result_environment env;
	if(const auto envs=root.elementsByTagName(SYSTEMINFO); envs.size()!=1)
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}
	else if(const auto env_opt=this->read_environment(envs.at(0)); !env_opt)
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}
	else
	{
		const auto clone_pairs=root.elementsByTagName(CLONE);
		shared_set<clone_pair> ps;
		for(int i=0; i<clone_pairs.size(); ++i)
		{
			if(const auto clone_pair_opt=this->read_clone(clone_pairs.at(i)); !clone_pair_opt)
			{
				qCritical()<<code_clone_loading_error::invalid_file_format;
				return nullptr;
			}
			else
			{
				ps.insert(clone_pair_opt.value());
			}
		}
		env=env_opt.value();
		return this->results_.empalce(std::move(env), std::move(ps));
	}

	qCritical()<<code_clone_loading_error::invalid_file_format;
	return nullptr;
}

std::optional<result_environment> nicad::reader::read_environment(const QDomNode &dom) noexcept
{
	if(!dom.isElement())
	{
		return std::nullopt;
	}

	if(const auto env=dom.toElement(); env.hasAttribute(PROCESSOR) && env.attribute(PROCESSOR).startsWith("nicad"))
	{
		result_environment e(clone_detector::nicad, this->source_);
		auto params=env.attributes();
		for(int i=0; i<params.size(); ++i)
		{
			if(params.item(i).isAttr())
			{
				const auto param=params.item(i).toAttr();
				e.add_parameter(param.name(), param.value());
			}
		}
		return e;
	}
	return std::nullopt;
}

std::optional<std::shared_ptr<clone_pair>> nicad::reader::read_clone(const QDomNode &dom) noexcept
{
	if(const auto children=dom.childNodes(); children.size()!=2 || !children.at(0).isElement() || !children.at(1).isElement())
	{
		return std::nullopt;
	}
	else if(const auto f1_opt=this->read_fragment(children.at(0)), f2_opt=this->read_fragment(children.at(1)); !f1_opt || !f2_opt)
	{
		return std::nullopt;
	}
	else if(const auto attributes=dom.attributes(); !attributes.contains(SIMILARITY))
	{
		return std::nullopt;
	}
	else if(const auto similarity_attribute=attributes.namedItem(SIMILARITY); !similarity_attribute.isAttr())
	{
		return std::nullopt;
	}
	else
	{
		const auto similarity=similarity_attribute.toAttr().value().toInt();
		return std::make_shared<clone_pair>(std::move(f1_opt.value()), std::move(f2_opt.value()), similarity);
	}
}

std::optional<fragment> nicad::reader::read_fragment(const QDomNode &dom) noexcept
{
	if(!dom.isElement())
	{
		return std::nullopt;
	}
	
	if(const auto f=dom.toElement(); !f.hasAttribute(FILE) || !f.hasAttribute(STARTLINE) || !f.hasAttribute(ENDLINE))
	{
		return std::nullopt;
	}
	else
	{
		const auto file_ptr=this->results_.emplace(f.attribute(FILE));
		return std::make_optional<fragment>(
			file_ptr,
			f.attribute(STARTLINE).toInt(),
			f.attribute(ENDLINE).toInt()
		);
	}
}

}