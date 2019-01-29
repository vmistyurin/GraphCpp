#include "core/random_graphs/non_oriented_graphs/random_non_oriented_graph_base.hpp"

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

void RandomNonOrientedGraphBase::factorize(const factorize_function& func, double probability)
{
	factorize_from(begin(), func, probability);
}

void RandomNonOrientedGraphBase::factorize_from(SymmetricMatrixIterator iter, const factorize_function& func, double probability)
{
	for (; iter != end(); ++iter)
	{
		const auto[i, j] = *iter;
		
		const auto vertex_probability = probability_at(i, j);
		if (!(are_doubles_equal(vertex_probability, 0) || are_doubles_equal(vertex_probability, 1)))
		{
			auto deleted_branch = with_deleted_edge(i, j);
			deleted_branch->factorize(func, probability * (1.0 - vertex_probability));

			probability *= vertex_probability;
			set_probability(i, j, 1);
		}
	}

	func(release_graph(), probability);
}

SymmetricMatrixIterator RandomNonOrientedGraphBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator RandomNonOrientedGraphBase::end() const
{
	return SymmetricMatrixIterator();
}
