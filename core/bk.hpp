#ifndef BK_HPP
#define BK_HPP

#include "matching_table.hpp"

namespace asterism
{

class bk_fuser final
{
public:
	static shared_set<clone_pair> run(const shared_list<detection_result> &results, const matching_table &m) noexcept;

private:
	static bool bron_kerbosch(shared_set<clone_pair> &r, QSet<query> &p, const QSet<query> &x, const matching_table &m) noexcept;
	static std::shared_ptr<clone_pair> maximal(const shared_set<clone_pair> &p) noexcept;
	static fragment maximal(const QVector<fragment> &fragment) noexcept;
};

}

#endif // BK_HPP
