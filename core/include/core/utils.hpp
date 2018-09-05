#ifndef GRAPH_CORE_UTILS_HPP
#define GRAPH_CORE_UTILS_HPP

#include <vector>

#include "core/macroses.hpp"
#include "core/graph_implementations/graph_base.hpp"
#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"
#include "core/matrix_implementations/non-symmetric_matrixes/non-symmetric_matrix_base.hpp"

namespace graphcpp
{
	bool is_permutation(const std::vector<msize>& candidate);
	std::vector<std::pair<msize, msize>> to_transpositions(const std::vector<msize>& permutation);

	bool check_symmetrical_matrix(const std::vector<std::vector<mcontent>>& candidate);
	bool is_matrix_from_graph(const SymmetricMatrixBase& matrix, const GraphBase& graph);
	bool is_matrix_from_graph(const NonSymmetricMatrixBase& matrix, const GraphBase& graph);

	template<class T, class V> 
	bool contains(const T& container, V&& value)
	{
		return std::find(container.cbegin(), container.cend(), value) != container.cend();
	}
}
#endif