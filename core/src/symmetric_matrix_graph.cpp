#include "core/GraphImplementation/symmetric_matrix_graph.h"

using namespace graphcpp;

SymmetricMatrixGraph::SymmetricMatrixGraph(const std::vector<Edge>& edges, unsigned int dimension)
{
	_matrix.resize(dimension);
	for (unsigned int i = 0; i < dimension; ++i)
	{
		_matrix[i].resize(dimension - i);
	}
	for (const auto& edge : edges)
	{
		_matrix[edge.v1()][edge.v2()] = true;
	}
}

unsigned int SymmetricMatrixGraph::Dimension() const noexcept
{
	return _matrix.size();
}

std::vector<std::vector<bool>> SymmetricMatrixGraph::GetMatrix() const noexcept
{
	return _matrix;
}

std::vector<Edge> SymmetricMatrixGraph::GetEdges() const noexcept
{
	return std::vector<Edge>();
}

std::vector<int> SymmetricMatrixGraph::GetLinkedVertexes(unsigned int vertex) const noexcept
{
	return std::vector<int>();
}