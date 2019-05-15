#include "core/graphs/non_oriented_graphs/non_oriented_graph_base.hpp"

#include <cassert>
#include <algorithm>
#include <queue>

using namespace graphcpp;

namespace
{
	void dfs_bridge_edition(const NonOrientedGraphBase& graph, msize vertex, msize ancestor, std::vector<bool>& used, 
		std::vector<msize>& times, std::vector<msize>& min_times, std::list<std::pair<msize, msize>>& bridges, msize& timer)
	{
		used[vertex] = true;
		times[vertex] = timer;
		min_times[vertex] = timer++;

		for (msize i = 0; i < graph.dimension(); i++)
		{
			if (graph.at(vertex, i) > 0 && i != ancestor)
			{
				if (used[i])
				{
					min_times[vertex] = std::min(min_times[vertex], times[i]);
				}
				else
				{
					dfs_bridge_edition(graph, i, vertex, used, times, min_times, bridges, timer);
					min_times[vertex] = std::min(min_times[vertex], min_times[i]);
					if (min_times[i] > times[vertex])
					{
						bridges.emplace_back(std::make_pair(vertex, i));
					}
				}
			}
		}
	}

	void get_chain(const NonOrientedGraphBase& graph, msize vertex, std::vector<msize>& chain)
	{
		auto linked_with = graph.get_linked_vertexes(vertex);
		if (linked_with.size() != 2)
		{
			chain.push_back(vertex);
			return;
		}

		auto next_vertex = (chain.back() == linked_with[0] ? linked_with[1] : linked_with[0]);
		chain.push_back(vertex);
		get_chain(graph, next_vertex, chain);
	}
}

// http://e-maxx.ru/algo/bridge_searching
// returns edge-bridges and classes
std::pair<std::list<std::pair<msize, msize>>, std::vector<msize>> NonOrientedGraphBase::get_bridges() const
{
	std::list<std::pair<msize, msize>> result;

	std::vector<bool> used(dimension());
	std::vector<msize> times(dimension());
	std::vector<msize> min_times(dimension());

	msize timer = 0;

	for (msize i = 0; i < used.size(); i++)
	{
		if (!used[i])
		{
			dfs_bridge_edition(*this, i, msize_undefined, used, times, min_times, result, timer);
		}
	}

	return std::pair(result, min_times);
}

std::vector<std::vector<msize>> NonOrientedGraphBase::get_chains() const
{
	std::vector<std::vector<msize>> result;
	std::vector<msize> chain_components(dimension());
	msize chain_counter = 0;

	for (msize i = 0; i < dimension(); i++)
	{
		if (chain_components[i] != 0)
		{
			continue;
		}
		auto linked_with = get_linked_vertexes(i);
		if (linked_with.size() != 2)
		{
			chain_components[i] = msize_undefined;
			continue;
		}

		std::vector<msize> chain;
		chain.push_back(i);

		get_chain(*this, linked_with[0], chain);
		std::reverse(chain.begin(), chain.end());
		get_chain(*this, linked_with[1], chain);

		for (auto vertex : chain)
		{
			chain_components[vertex] = chain_counter;
		}

		result.emplace_back(std::move(chain));
		chain_counter++;
	}

	return result;
}

bool NonOrientedGraphBase::is_tree() const
{
    return get_connected_component(0).size() == dimension() && get_number_of_edges() == dimension() - 1;
}

SymmetricMatrixIterator NonOrientedGraphBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator NonOrientedGraphBase::end() const
{
	return SymmetricMatrixIterator();
}