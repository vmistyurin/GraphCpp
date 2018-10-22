#pragma once

#include <cassert>
#include <vector>
#include <algorithm>

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

	template<class ContainerType, class ValueType>
	bool contains(const ContainerType& container, ValueType&& value)
	{
		return std::find(container.cbegin(), container.cend(), value) != container.cend();
	}

	template<class ValueType>
	void apply_permutation_with_transpositions(std::vector<ValueType>& target, const std::vector<msize>& permutation)
	{
		assert(is_permutation(permutation));
		assert(target.size() == permutation.size());

		auto transpositions = to_transpositions(permutation);

		for (auto[index1, index2] : transpositions)
		{
			std::swap(target[index1], target[index2]);
		}
	}

	template<class ValueType>
	std::vector<mcontent> apply_permutation_alloc(const std::vector<ValueType>& target, const std::vector<msize>& permutation)
	{
		assert(is_permutation(permutation));
		assert(target.size() == permutation.size());

		std::vector<mcontent> result(target.size());

		for (msize i = 0; i < target.size(); i++)
		{
			result[permutation[i]] = target[i];
		}

		return result;
	}
    
    bool is_doubles_equal(double value1, double value2);
}
