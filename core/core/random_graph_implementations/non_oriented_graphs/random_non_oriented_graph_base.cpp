#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph_base.hpp"

#include "core/utils/numeric.hpp"

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


SymmetricMatrixIterator RandomNonOrientedGraphBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator RandomNonOrientedGraphBase::end() const
{
	return SymmetricMatrixIterator();
}
