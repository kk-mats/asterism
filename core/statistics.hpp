#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <QMap>
#include <string>

#include "detection_results.hpp"

namespace asterism
{


class statistics
{
public:
	statistics(const detection_results &results) noexcept
	{
		for(const auto &r:results.results())
		{
			QMap<int, shared_vector<clone_pair>> d;
			for(const auto &p:r->clone_pairs())
			{
				for(const auto &f:{p->fragment1(), p->fragment2()})
				{
					if(!d.contains(f.length()))
					{
						d.insert(f.length(), shared_vector<clone_pair>(1, p));
					}
					else
					{
						d[f.length()].append(p);
					}
				}
			}

			this->clone_length_distributions_[r]=d;
		}
	}

private:
	QMap<std::shared_ptr<detection_result>, QMap<int, shared_vector<clone_pair>>> clone_length_distributions_;


};

}

#endif // STATISTICS_HPP
