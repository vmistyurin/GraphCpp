#include "core/graphs/graph_base.hpp"

#include <cassert>
#include <algorithm>
#include <queue>
#include <set>

using namespace graphcpp;

namespace
{
	std::vector<msize> get_reversed_path_from_bfs_tree(const std::vector<msize>& partial_tree, msize start, msize finish)
	{
		std::vector<msize> result;

		auto current_vertex = finish;
		while (current_vertex != start)
		{
			result.push_back(current_vertex);
			current_vertex = partial_tree[current_vertex];
		}
		result.push_back(start);

		return result;
	}
}

void GraphBase::reduce_edge(msize v1, msize v2, mcontent amount)
{
	assert(v1 != v2);
	assert(std::max(v1, v2) < dimension());
	assert(amount <= at(v1, v2));

	const auto previous_value = at(v1, v2);
	set(v1, v2, previous_value - amount);
}

std::vector<msize> GraphBase::get_degrees() const
{
	std::vector<msize> result(dimension());

	for (msize i = 0; i < dimension(); i++)
	{
		result[i] = get_degree(i);
	}

	return result;
}

std::vector<msize> GraphBase::get_linked_vertexes(msize vertex) const
{
	assert(vertex < dimension());

	std::vector<msize> result;
	for (msize i = 0; i < dimension(); i++)
	{
		if (at(vertex, i) > 0)
		{
			result.push_back(i);
		}
	}
	return result;
}

msize GraphBase::get_degree(msize vertex) const
{
	assert(vertex < dimension());

	msize result = 0;
	for (msize i = 0; i < dimension(); i++)
	{
		if (at(vertex, i) > 0)
		{
			result++;
		}
	}
	return result;
}

std::optional<std::vector<msize>> graphcpp::get_random_path(const GraphBase& graph, msize start, msize finish)
{
	assert(std::max(start, finish) < graph.dimension());

	std::vector<msize> ancestors(graph.dimension(), msize_undefined);
	ancestors[start] = start;
	std::queue<msize> queue;

	queue.push(start);

	while (!queue.empty())
	{
		const auto current_vertex = queue.front(); queue.pop();
		for (msize i = 0; i < graph.dimension(); i++)
		{
			if (graph.at(current_vertex, i) > 0 && (ancestors[i] == msize_undefined))
			{
				ancestors[i] = current_vertex;
				if (finish == i)
				{
					return get_reversed_path_from_bfs_tree(ancestors, start, finish);
				}
				queue.push(i);
			}
		}
	}
	return std::nullopt;
}

std::vector<msize> graphcpp::get_connected_component(const GraphBase& graph, msize vertex)
{
	assert(vertex < graph.dimension());

	std::set<msize> result;
	std::queue<msize> queue;

	result.insert(vertex);
	queue.push(vertex);

	while (!queue.empty())
	{
		auto current_vertex = queue.front(); queue.pop();
		for (msize i = 0; i < graph.dimension(); i++)
		{
			if (graph.at(current_vertex, i) > 0)
			{
				if (auto [it, success] = result.insert(i); success)
				{
					(void)it;
					queue.push(i);
				}
			}
		}
	}

	return std::vector<msize>(result.cbegin(), result.cend());
}
