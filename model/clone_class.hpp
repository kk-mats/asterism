#ifndef CLONE_CLASS_HPP
#define CLONE_CLASS_HPP

#include <vector>
#include <functional>

#include <QSet>
#include <BronKerbosch/bron-kerbosch_utils.h>

#include "clone_pair.hpp"

namespace asterism
{

using clone_class=QSet<fragment>;

void edge(BronKerbosch::Graph<fragment> &G, const std::shared_ptr<clone_pair> &p);

void aggregator(std::forward_list<BronKerbosch::Graph<fragment>> &all, BronKerbosch::Graph<fragment> R, BronKerbosch::Graph<fragment> P, BronKerbosch::Graph<fragment>);

std::vector<clone_class> to_clone_class(const shared_set<clone_pair> &clone_pairs);

}

#endif // CLONE_CLASS_HPP