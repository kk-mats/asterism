#include "csv.hpp"

namespace asterism
{

bool csv::write(const detection_result &result, const QString &project_root, const QString &path) noexcept
{
	QFile file(path);

	if(!file.open(QIODevice::WriteOnly))
	{
		qCritical()<<code_clone_loading_error::file_not_found<<path;
		return false;
	}

	if(!writer(&file, project_root).write(result))
	{
		return false;
	}

	qInfo()<<"write to "<<path;
	return true;
}

csv::writer::writer(QFile *f, const QString &project_root) noexcept
	: os_(f), project_root_(project_root)
{}

bool csv::writer::write(const detection_result &result) noexcept
{
	for(const auto &h:header_)
	{
		this->os_<<h<<",";
	}
	this->os_<<endl;

	for(const auto &p:result.clone_pairs())
	{
		if(!this->write(p))
		{
			return false;
		}
		this->os_<<endl;
	}
	return true;
}

bool csv::writer::write(const std::shared_ptr<clone_pair> &clone_pair) noexcept
{
	return this->write(clone_pair->fragment1()) && this->write(clone_pair->fragment2());
}

bool csv::writer::write(const fragment &fragment) noexcept
{
	auto subdir_str=fragment.file_ptr()->canonical_file_path();
	QFileInfo sub_dir_file(subdir_str.remove(this->project_root_.canonicalPath()));
	if(const auto filename=sub_dir_file.fileName(); !filename.isEmpty())
	{
		this->os_<<sub_dir_file.path()<<","<<filename<<","<<fragment.begin()<<", "<<fragment.end()<<", ";
		return true;
	}
	return false;
}

}
