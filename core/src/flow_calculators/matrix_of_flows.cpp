#include "core/flow_calculators.hpp"

#include "core/matrix_implementations/symmetric_matrixes/half_symmetric_matrix.hpp"

using namespace graphcpp;

using SymmetricMatrixType = HalfSymmetricMatrix;

std::unique_ptr<SymmetricMatrixBase> flow_calculators::matrix_of_flows(const NonOrientedGraphBase& graph,
	const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator)
{
	auto result = std::make_unique<SymmetricMatrixType>(graph.dimension());

	for (auto[i, j] : graph)
	{
		result->set(i, j, single_flow_calculator(graph, i, j));
	}

	return result;
}
