#pragma once

#include <cassert>
#include <istream>

#include "core/random_graphs/non_oriented_graphs/random_non_oriented_graph_base.hpp"

namespace graphcpp
{
    template<class NorGraphType, class SymMatrixType>
    class RandomNonOrientedGraph final: public RandomNonOrientedGraphBase
    {
	public:
		IS_NOR_GRAPH_IMPL(NorGraphType);
		IS_SYM_MATRIX_IMPL(SymMatrixType);

		using GraphType = NorGraphType;
		using MatrixType = SymMatrixType;
		
    private:
        NorGraphType _graph;
        SymMatrixType _probabilities;

    public:
        RandomNonOrientedGraph(const std::vector<SymmetricRandomEdge>& edges, msize dimension);
		RandomNonOrientedGraph(NorGraphType&& graph, SymMatrixType&& probabilities);

		static RandomNonOrientedGraph<NorGraphType, SymMatrixType> read_from_stream(std::istream& stream);

        msize dimension() const override;
        mcontent at(msize index1, msize index2) const override;
        void set(msize index1, msize index2, mcontent value) override;

        double probability_at(msize index1, msize index2) const override;
        void set_probability(msize index1, msize index2, double value) override;	

		void delete_vertexes(const std::vector<msize>& vertexes) override;
		RandomNonOrientedGraph<NorGraphType, SymMatrixType> with_deleted_vertexes(const std::vector<msize>& vertexes) const;
		RandomNonOrientedGraph<NorGraphType, SymMatrixType> with_deleted_edge(msize i, msize j) const;

		std::unique_ptr<NonOrientedGraphBase> release_graph() override;

		const NorGraphType& graph() const;
		const SymMatrixType& probabilities() const;

		RandomNonOrientedGraph extract_subgraph(const std::vector<msize>& vertexes) const;
    };

    template<class NorGraphType, class SymMatrixType>
    RandomNonOrientedGraph<NorGraphType, SymMatrixType>::RandomNonOrientedGraph(const std::vector<SymmetricRandomEdge>& edges, msize dimension) :
		_graph(dimension), _probabilities(dimension)
    {
        for (const auto& edge : edges) 
		{
            assert(std::max(edge.v1(), edge.v2()) < dimension);
            _graph.set(edge.v1(), edge.v2(), edge.weight());
            _probabilities.set(edge.v1(), edge.v2(), edge.probability());
        }
    }

	template<class NorGraphType, class SymMatrixType>
	RandomNonOrientedGraph<NorGraphType, SymMatrixType>::RandomNonOrientedGraph(NorGraphType&& graph, SymMatrixType&& probabilities) :
		_graph(std::move(graph)), _probabilities(std::move(probabilities))
	{
	}

	template<class NorGraphType, class SymMatrixType>
	RandomNonOrientedGraph<NorGraphType, SymMatrixType> RandomNonOrientedGraph<NorGraphType, SymMatrixType>::read_from_stream(std::istream& stream)
	{
		msize dimension, number_of_edges;
		stream >> dimension >> number_of_edges;

		RandomNonOrientedGraph<NorGraphType, SymMatrixType> graph({}, dimension);

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

    template<class NorGraphType, class SymMatrixType>
    msize RandomNonOrientedGraph<NorGraphType, SymMatrixType>::dimension() const
    {
        return _graph.dimension();
    }

    template<class NorGraphType, class SymMatrixType>
    mcontent RandomNonOrientedGraph<NorGraphType, SymMatrixType>::at(msize index1, msize index2) const
    {
        assert(std::max(index1, index2) < dimension());
        return _graph.at(index1, index2);
    }

    template<class NorGraphType, class SymMatrixType>
    void RandomNonOrientedGraph<NorGraphType, SymMatrixType>::set(msize index1, msize index2, mcontent value)
    {
        assert(std::max(index1, index2) < dimension());
        _graph.set(index1, index2, value);
    }

    template<class NorGraphType, class SymMatrixType>
    double RandomNonOrientedGraph<NorGraphType, SymMatrixType>::probability_at(msize index1, msize index2) const
    {
        return _probabilities.at(index1, index2);
    }

    template<class NorGraphType, class SymMatrixType>
    void RandomNonOrientedGraph<NorGraphType, SymMatrixType>::set_probability(msize index1, msize index2, double value)
    {
        _probabilities.set(index1, index2, value);
    }

	template<class NorGraphType, class SymMatrixType>
	void RandomNonOrientedGraph<NorGraphType, SymMatrixType>::delete_vertexes(const std::vector<msize>& vertexes)
	{
		_probabilities.delete_strings(vertexes);
		_graph.delete_vertexes(vertexes);
	}

	template<class NorGraphType, class SymMatrixType>
	RandomNonOrientedGraph<NorGraphType, SymMatrixType> RandomNonOrientedGraph<NorGraphType, SymMatrixType>::with_deleted_vertexes(const std::vector<msize>& vertexes) const
	{
		auto probabilities = _probabilities.template with_deleted_vertexes<SymMatrixType>(vertexes);
		auto graph = _graph.template with_deleted_vertexes<NorGraphType, SymMatrixType>(vertexes);

		return RandomNonOrientedGraph<NorGraphType, SymMatrixType>(std::move(graph), std::move(probabilities));
	}

	template<class NorGraphType, class SymMatrixType>
	RandomNonOrientedGraph<NorGraphType, SymMatrixType> RandomNonOrientedGraph<NorGraphType, SymMatrixType>::with_deleted_edge(msize i, msize j) const
	{
		auto probabilities = _probabilities.template with_deleted_element<SymMatrixType>(i, j);
		auto graph = _graph.template with_deleted_edge<NorGraphType, SymMatrixType>(i, j);

		return RandomNonOrientedGraph<NorGraphType, SymMatrixType>(std::move(graph), std::move(probabilities));
	}

	template<class NorGraphType, class SymMatrixType>
	std::unique_ptr<NonOrientedGraphBase> RandomNonOrientedGraph<NorGraphType, SymMatrixType>::release_graph()
	{		
		return std::make_unique<NorGraphType>(std::move(_graph));
	}

	template<class NorGraphType, class SymMatrixType>
	const NorGraphType& RandomNonOrientedGraph<NorGraphType, SymMatrixType>::graph() const
	{		
		return _graph;
	}

	template<class NorGraphType, class SymMatrixType>
	const SymMatrixType& RandomNonOrientedGraph<NorGraphType, SymMatrixType>::probabilities() const
	{		
		return _probabilities;
	}

	template<class NorGraphType, class SymMatrixType>
	RandomNonOrientedGraph<NorGraphType, SymMatrixType> RandomNonOrientedGraph<NorGraphType, SymMatrixType>::extract_subgraph(const std::vector<msize>& vertexes) const
	{		
		return RandomNonOrientedGraph<NorGraphType, SymMatrixType>(
			_graph.extract_subgraph(vertexes),
			_probabilities.extract_matrix(vertexes)
		);
	}

}
