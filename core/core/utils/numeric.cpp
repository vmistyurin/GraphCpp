#include "core/utils/numeric.hpp"

#include <cmath>
#include <numeric>

#include "core/matrices/non_symmetric_matrices/non_symmetric_matrix_base.hpp"
#include "core/matrices/symmetric_matrices/symmetric_matrix_base.hpp"
#include "core/graphs/graph_base.hpp"

using namespace graphcpp;

bool graphcpp::is_permutation(const std::vector<msize>& candidate)
{
	std::vector<msize> const_permutation; const_permutation.resize(candidate.size());
	std::iota(const_permutation.begin(), const_permutation.end(), 0);
	return std::is_permutation(candidate.cbegin(), candidate.cend(), const_permutation.cbegin(), const_permutation.cend());
}

std::vector<std::pair<msize, msize>> graphcpp::to_transpositions(const std::vector<msize>& permutation)
{
	assert(is_permutation(permutation));
	std::vector<std::vector<msize>> cycles;

	std::vector<bool> used(permutation.size());

	for(msize i = 0; i < permutation.size(); i++)
	{
		if (!used[i])
		{
			msize j = i;
			std::vector<msize> current_cycle;
			do
			{
				current_cycle.push_back(j);
				used[j] = true;
				j = permutation[j];
			} while (j != i);
			cycles.push_back(current_cycle);
		}
	}

	std::vector<std::pair<msize, msize>> result;

	for (auto cycle : cycles)
	{
		if (cycle.size() > 1)
		{
			for (msize i = 1; i < cycle.size(); i++)
			{
				result.push_back(std::make_pair(cycle[0], cycle[i]));
			}
		}
	}

	return result;
}

bool graphcpp::check_symmetrical_matrix(const std::vector<std::vector<mcontent>>& candidate)
{
	for (auto str : candidate)
	{
		RETURN_IF(str.size() != candidate.size(), false);
	}
	for (msize i = 1; i < candidate.size(); i++)
	{
		for (msize j = 0; j < i; j++)
		{
			RETURN_IF(candidate[i][j] != candidate[j][i], false);
		}
	}

	return true;
}

bool graphcpp::is_matrix_from_graph(const SymmetricMatrixBase& matrix, const GraphBase& graph)
{
	for (auto[i, j] : matrix)
	{
		RETURN_IF(matrix.at(i, j) != graph.at(i, j), false);
	}
	return true;
}

bool graphcpp::is_matrix_from_graph(const NonSymmetricMatrixBase& matrix, const GraphBase& graph)
{
	for (auto[i, j] : matrix)
	{
		RETURN_IF(matrix.at(i, j) != graph.at(i, j), false);
	}
	return true;
}

bool graphcpp::are_doubles_equal(double value1, double value2)
{
    return std::fabs(value1 - value2) < 0.00000000000001;
}

std::vector<msize> graphcpp::find_addition(const std::vector<msize>& numbers, msize length)
{
    assert(!numbers.empty());
    assert(std::all_of(numbers.cbegin(), numbers.cend(), [&](auto number) { return number < length; } ));
    
    std::vector<msize> result;
    result.reserve(length - numbers.size());
    
    for (msize i = 0; i < length; i++)
    {
        if (!contains(numbers, i))
        {
            result.push_back(i);
        }
    }
    
    return result;
}

std::vector<msize> graphcpp::reduce_vertexes_numbers(const std::vector<msize>& current_vertexes, const std::vector<msize>& missing_vertexes)
{
    std::vector<msize> result;
    result.reserve(missing_vertexes.size());
    
    for (msize i = 0; i < current_vertexes.size(); i++)
    {
        result.push_back(current_vertexes[i] - std::count_if(missing_vertexes.cbegin(), missing_vertexes.cend(), [&](auto vertex)
        {
            return vertex < current_vertexes[i];
        }));
    }
    
    return result;
}

