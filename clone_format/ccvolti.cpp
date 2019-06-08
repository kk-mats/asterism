#include "ccvolti.hpp"

namespace asterism
{

std::shared_ptr<detection_result> ccvolti::read(const QString &path, detection_results &results) noexcept
{
	QFile file(path);

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qCritical()<<code_clone_loading_error::file_not_found<<path;
		return nullptr;
	}
	return reader(file).read(path, results);
}

ccvolti::reader::reader(QFile &file) noexcept
	: is_(&file)
{}

std::shared_ptr<detection_result> ccvolti::reader::read(const QString &path, detection_results &results) noexcept
{
	if(!this->read_header())
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return nullptr;
	}

	shared_set<clone_pair> clone_pair_set;
	while(!this->is_.atEnd())
	{
		if(auto p=this->read_line(results); p!=nullptr)
		{
			clone_pair_set.insert(p);
		}
		else
		{
			return nullptr;
		}
	}

	return results.empalce(result_environment(clone_detector::ccvolti, path), std::move(clone_pair_set));
}

bool ccvolti::reader::read_header() noexcept
{
	auto header=this->is_.readLine().split(',', QString::SkipEmptyParts);
	int i=0;
	int found=0;
	for(auto &&h:header)
	{
		h=h.trimmed();
		if(h=="A class name")
		{
			this->a_class_name_=i;
		}
		else if(h=="B class name")
		{
			this->b_class_name_=i;
		}
		else if(h=="A start line")
		{
			this->a_start_line_=i;
		}
		else if(h=="A end line")
		{
			this->a_end_line_=i;
		}
		else if(h=="B start line")
		{
			this->b_start_line_=i;
		}
		else if(h=="B end line")
		{
			this->b_end_line_=i;
		}
		else if(h=="similarity")
		{
			this->similarity_=i;
		}
		else
		{
			++i;
			continue;
		}
		++i;
		++found;
	}

	return found==7;
}

std::shared_ptr<clone_pair> ccvolti::reader::read_line(detection_results &results) noexcept
{
	auto line=this->is_.readLine().split(',', QString::SkipEmptyParts);
	auto f1=this->read_fragment(this->a_class_name_, this->a_start_line_, this->a_end_line_, line, results);
	auto f2=this->read_fragment(this->b_class_name_, this->b_start_line_, this->b_end_line_, line, results);
	bool similarity_ok;
	const auto similarity=int(line[this->similarity_].toDouble(&similarity_ok)*100);

	if(f1 && f2 && similarity_ok)
	{
		return std::make_shared<clone_pair>(f1.value(), f2.value(), similarity);
	}
	return nullptr;
}

std::optional<fragment> ccvolti::reader::read_fragment(const int class_name, const int start_line, const int end_line, const QStringList &line, detection_results &results) const noexcept
{
	auto file=to_canonical_file_path(line[class_name]);
	if(file.isEmpty())
	{
		qCritical()<<code_clone_loading_error::file_not_found;
		return std::nullopt;
	}
	bool start_ok, end_ok;
	const int start=line[start_line].toInt(&start_ok);
	const int end=line[end_line].toInt(&end_ok);

	if(!start_ok || !end_ok)
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return std::nullopt;
	}

	return std::make_optional<fragment>(results.emplace(std::move(file)), start, end);
}

}
