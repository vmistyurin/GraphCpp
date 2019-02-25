#pragma once

#include <cassert>
#include <istream>

#include "core/random_graphs/non_oriented_graphs/random_non_oriented_graph_base.hpp"

namespace graphcpp
{
    template<class GraphType, class MatrixType>
    class RandomNonOrientedGraph final: public RandomNonOrientedGraphBase
    {
		IS_NOR_GRAPH_IMPL(GraphType);
		IS_SYM_MATRIX_IMPL(MatrixType);
		
    private:
        GraphType _graph;
        MatrixType _probabilities;

    public:
        RandomNonOrientedGraph(const std::vector<SymmetricRandomEdge>& edges, msize dimension);
		RandomNonOrientedGraph(GraphType&& graph, MatrixType&& probabilities);

		static RandomNonOrientedGraph<GraphType, MatrixType> read_from_stream(std::istream& stream);

        msize dimension() const override;
        mcontent at(msize index1, msize index2) const override;
        void set(msize index1, msize index2, mcontent value) override;

        double probability_at(msize index1, msize index2) const override;
        void set_probability(msize index1, msize index2, double value) override;	

		void delete_vertexes(const std::vector<msize>& vertexes) override;
		std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const override;
		std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_edge(msize i, msize j) const override;

		std::unique_ptr<NonOrientedGraphBase> release_graph() override;
    };

    template<class GraphType, class MatrixType>
    RandomNonOrientedGraph<GraphType, MatrixType>::RandomNonOrientedGraph(const std::vector<SymmetricRandomEdge>& edges, msize dimension) :
		_graph(dimension), _probabilities(dimension)
    {
        for (const auto& edge : edges) 
		{
            assert(std::max(edge.v1(), edge.v2()) < dimension);
            _graph.set(edge.v1(), edge.v2(), edge.weight());
            _probabilities.set(edge.v1(), edge.v2(), edge.probability());
        }
    }

	template<class GraphType, class MatrixType>
	RandomNonOrientedGraph<GraphType, MatrixType>::RandomNonOrientedGraph(GraphType&& graph, MatrixType&& probabilities) :
		_graph(std::move(graph)), _probabilities(std::move(probabilities))
	{
	}

	template<class GraphType, class MatrixType>
	RandomNonOrientedGraph<GraphType, MatrixType> RandomNonOrientedGraph<GraphType, MatrixType>::read_from_stream(std::istream& stream)
	{
		msize dimension, number_of_edges;
		stream >> dimension >> number_of_edges;

		RandomNonOrientedGraph<GraphType, MatrixType> graph({}, dimension);

		for (msize i = 0; i < number_of_edges; i++)
		{
			msize v1, v2;
			mcontent weight;
			double probability;

			stream >> v1 >> v2 >> weight >> probability;

			graph.set(v1, v2, weight);
			graph.set_probability(v1, v2, probability);
		}

		return graph;
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

	template<class GraphType, class MatrixType>
	std::unique_ptr<RandomNonOrientedGraphBase> RandomNonOrientedGraph<GraphType, MatrixType>::with_deleted_vertexes(const std::vector<msize>& vertexes) const
	{
		auto probabilities = _probabilities.template with_deleted_vertexes<MatrixType>(vertexes);
		auto graph = _graph.template with_deleted_vertexes<GraphType, MatrixType>(vertexes);

		return std::make_unique<RandomNonOrientedGraph<GraphType, MatrixType>>(std::move(graph), std::move(probabilities));
	}

	template<class GraphType, class MatrixType>
	std::unique_ptr<RandomNonOrientedGraphBase> RandomNonOrientedGraph<GraphType, MatrixType>::with_deleted_edge(msize i, msize j) const
	{
		auto probabilities = _probabilities.template with_deleted_element<MatrixType>(i, j);
		auto graph = _graph.template with_deleted_edge<GraphType, MatrixType>(i, j);

		return std::make_unique<RandomNonOrientedGraph<GraphType, MatrixType>>(std::move(graph), std::move(probabilities));
	}

	template<class GraphType, class MatrixType>
	std::unique_ptr<NonOrientedGraphBase> RandomNonOrientedGraph<GraphType, MatrixType>::release_graph()
	{		
		return std::make_unique<GraphType>(std::move(_graph));
	}
}
