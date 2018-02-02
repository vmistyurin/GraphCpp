#ifndef GRAPH_CORE_UTILS_H
#define GRAPH_CORE_UTILS_H

#include "core/macroses.h"
#include <vector>

namespace graphcpp
{
	bool is_permutation(const std::vector<msize>& candidate);
	std::vector<std::pair<msize, msize>> to_transpositions(const std::vector<msize>& permutation);

	bool check_symmetrical_matrix(const std::vector<std::vector<mcontent>>& candidate);
}
#endif