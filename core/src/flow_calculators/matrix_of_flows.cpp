#include "core/flow_calculators/flow_calculators.hpp"

#include "core/matrix_implementations/matrix_implementations.hpp"

using namespace graphcpp;

template<class SymMatrixType>
std::unique_ptr<SymMatrixType> flow_calculators::matrix_of_flows(const NonOrientedGraphBase& graph,
	const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator)
{
	auto result = std::make_unique<SymMatrixType>(graph.dimension());

	for (auto[i, j] : graph)
	{
		result->set(i, j, single_flow_calculator(graph, i, j));
	}

	return result;
}

template<>
std::unique_ptr<SingleVectorSymmetricMatrix> flow_calculators::matrix_of_flows(const NonOrientedGraphBase& graph,
    const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator);

template<>
std::unique_ptr<FullSymmetricMatrix> flow_calculators::matrix_of_flows(const NonOrientedGraphBase& graph,
    const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator);

template<>
std::unique_ptr<HalfSymmetricMatrix> flow_calculators::matrix_of_flows(const NonOrientedGraphBase& graph,
    const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator);
