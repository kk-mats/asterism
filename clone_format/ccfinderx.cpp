#include "ccfinderx.hpp"

namespace asterism
{

std::shared_ptr<detection_result> ccfinderx::read(const QString &path, detection_results &results) noexcept
{
	QFile file(path);

	if(!file.open(QIODevice::ReadOnly))
	{
		qCritical()<<code_clone_loading_error::file_not_found<<path;
		return nullptr;
	}


	return reader(file).read(results);
}

ccfinderx::reader::reader(QFile &file) noexcept
	: is_(&file)
{
}

std::shared_ptr<detection_result> ccfinderx::reader::read(detection_results &results) noexcept
{
	this->check_version();





	return std::shared_ptr<detection_result>();
}

bool ccfinderx::reader::check_version() noexcept
{
	char *magic_number;
	if(const int r=this->is_.readRawData(magic_number, ccfinderx::magic_number.size()); r!=-1 || ccfinderx::magic_number!=magic_number)
	{
		qCritical()<<code_clone_loading_error::invalid_file_format;
		return false;
	}
	this->is_.skipRawData(sizeof(int32_t)*3);
	return true;
}

}

