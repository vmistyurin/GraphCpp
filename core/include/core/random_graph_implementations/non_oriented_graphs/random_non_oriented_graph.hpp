#pragma once

#include <cassert>

#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph_base.hpp"

namespace graphcpp
{
    template<class GraphType, class MatrixType>
    class RandomNonOrientedGraph final: public RandomNonOrientedGraphBase
    {
    private:
        GraphType _graph;
        MatrixType _probabilities;

    public:
        RandomNonOrientedGraph(const std::vector<SymmetricRandomEdge>& edges, msize dimension);

        msize dimension() const override;
        mcontent at(msize index1, msize index2) const override;
        void set(msize index1, msize index2, mcontent value) override;

        double probability_at(msize index1, msize index2) const override;
        void set_probability(msize index1, msize index2, double value) override;	

		void delete_vertexes(const std::vector<msize>& vertexes) override;
    };

    template<class GraphType, class MatrixType>
    RandomNonOrientedGraph<GraphType, MatrixType>::RandomNonOrientedGraph(const std::vector<SymmetricRandomEdge>& edges, msize dimension) :
            _graph(dimension), _probabilities(dimension)
    {
        for (const auto& edge : edges) {
            assert(std::max(edge.v1(), edge.v2()) < dimension);
            _graph.set(edge.v1(), edge.v2(), edge.weight());
            _probabilities.set(edge.v1(), edge.v2(), edge.probability());
        }
    }

    template<class GraphType, class MatrixType>
    msize RandomNonOrientedGraph<GraphType, MatrixType>::dimension() const
    {
        return _graph.dimension();
    }

    template<class GraphType, class MatrixType>
    mcontent RandomNonOrientedGraph<GraphType, MatrixType>::at(msize index1, msize index2) const
    {
        assert(std::max(index1, index2) < dimension());
        return _graph.at(index1, index2);
    }

    template<class GraphType, class MatrixType>
    void RandomNonOrientedGraph<GraphType, MatrixType>::set(msize index1, msize index2, mcontent value)
    {
        assert(std::max(index1, index2) < dimension());
        _graph.set(index1, index2, value);
    }

    template<class GraphType, class MatrixType>
    double RandomNonOrientedGraph<GraphType, MatrixType>::probability_at(msize index1, msize index2) const
    {
        return _probabilities.at(index1, index2);
    }

    template<class GraphType, class MatrixType>
    void RandomNonOrientedGraph<GraphType, MatrixType>::set_probability(msize index1, msize index2, double value)
    {
        _probabilities.set(index1, index2, value);
    }

	template<class GraphType, class MatrixType>
	void RandomNonOrientedGraph<GraphType, MatrixType>::delete_vertexes(const std::vector<msize>& vertexes)
	{
		_probabilities.delete_strings(vertexes);
		_graph.delete_vertexes(vertexes);
	}
}
