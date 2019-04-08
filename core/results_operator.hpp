#ifndef RESULTS_OPERATOR_HPP
#define RESULTS_OPERATOR_HPP

#include "matching_table.hpp"
#include "clone_format/clone_io.hpp"
#include "layer/heatmap_layer.hpp"

namespace asterism
{

class results_operator
{
public:
	results_operator();



private:
	detection_results detection_results_;
};

}

#endif // RESULTS_OPERATOR_HPP
