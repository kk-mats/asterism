#ifndef JCLN_HPP
#define JCLN_HPP

#include <QDir>
#include <QJsonDocument>

#include "model/detection_result.hpp"

namespace asterism
{

class jcln
{
public:
	static detection_result parse(const QDir &path);
	static bool write(const detection_results &results, const QDir &path);

};

}

#endif // JCLN_HPP
