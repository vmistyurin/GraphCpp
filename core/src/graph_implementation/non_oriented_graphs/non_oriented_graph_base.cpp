#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"

#include <algorithm>

using namespace graphcpp;

namespace
{
	void dfs(const NonOrientedGraphBase& graph, msize vertex, msize ancestor, std::vector<bool>& used, 
		std::vector<msize>& times, std::vector<msize>& min_times, std::list<std::pair<msize, msize>>& bridges, msize& timer)
	{
		used[vertex] = true;
		times[vertex] = timer;
		min_times[vertex] = timer++;

		for(msize i = 0; i < graph.dimension(); i++)
		{
			if(graph.at(vertex, i) > 0 && i != ancestor)
			{
				if(used[i])
				{
					min_times[vertex] = std::min(min_times[vertex], times[i]);
				}
				else
				{
					dfs(graph, i, vertex, used, times, min_times, bridges, timer);
					min_times[vertex] = std::min(min_times[vertex], min_times[i]);
					if(min_times[i] > times[vertex])
					{
						bridges.emplace_back(std::make_pair(vertex, i));
					}
				}
			}
		}
	}
}

//http://e-maxx.ru/algo/bridge_searching
std::list<std::pair<msize, msize>> NonOrientedGraphBase::get_bridges() const
{
	std::list<std::pair<msize, msize>> result;

	std::vector<bool> used(dimension());
	std::vector<msize> times(dimension());
	std::vector<msize> min_times(dimension());

	msize timer = 0;

	for(msize i = 0; i < used.size(); i++)
	{
		if (!used[i])
		{
			dfs(*this, i, msize_undefined, used, times, min_times, result, timer);
		}
	}

	return result;
}

SymmetricMatrixIterator NonOrientedGraphBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator NonOrientedGraphBase::end() const
{
	return SymmetricMatrixIterator();
}