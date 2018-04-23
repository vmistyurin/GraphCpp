#include "core/utils.hpp"

#include <assert.h>
#include <numeric>
#include <algorithm>

using namespace graphcpp;

bool graphcpp::is_permutation(const std::vector<msize>& candidate)
{
	std::vector<int> const_permutation; const_permutation.resize(candidate.size());
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
