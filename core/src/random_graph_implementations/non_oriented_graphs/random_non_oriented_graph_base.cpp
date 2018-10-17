#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph_base.hpp"

using namespace graphcpp;

std::vector<SymmetricRandomEdge> RandomNonOrientedGraphBase::get_edges() const
{
	std::vector<SymmetricRandomEdge> result;

	for (auto[i, j] : *this)
	{
		const auto weight = at(i, j);
		if (weight > 0)
		{
			result.emplace_back(SymmetricRandomEdge(SymmetricEdge(i, j, weight), probability_at(i, j)));
		}
	}

	return result;
}

void RandomNonOrientedGraphBase::factorize(const factorize_function& func)
{
	factorize_from(begin(), func);
}

void RandomNonOrientedGraphBase::factorize_from(SymmetricMatrixIterator iter, const factorize_function& func)
{
	for (; iter != end(); ++iter)
	{
		const auto[i, j] = *iter;
		
		const auto vertex_probability = probability_at(i, j);
		if (vertex_probability != 0)
		{
			auto deleted_branch = with_deleted_vertexes({ i });
			deleted_branch->factorize(func);

			//func(this, vertex_probability);
		}
	}
}

SymmetricMatrixIterator RandomNonOrientedGraphBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator RandomNonOrientedGraphBase::end() const
{
	return SymmetricMatrixIterator();
}
