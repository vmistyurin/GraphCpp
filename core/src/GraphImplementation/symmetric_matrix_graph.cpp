#include "core/GraphImplementation/symmetric_matrix_graph.h"
#include <assert.h>
#include <limits>

using namespace graphcpp;

SymmetricMatrixGraph::SymmetricMatrixGraph(const std::vector<Edge>& edges, ushort dimension)
{
	_matrix.resize(dimension);
	for (ushort i = 0; i < dimension; ++i)
	{
		_matrix[i].resize(dimension - i);
	}
	for (const auto& edge : edges)
	{
		_matrix[edge.v1()][edge.v2()] = true;
	}
}

ushort SymmetricMatrixGraph::Dimension() const noexcept
{
	assert(_matrix.size() < std::numeric_limits<ushort>::max());
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

std::vector<ushort> SymmetricMatrixGraph::GetLinkedVertexes(ushort vertex) const noexcept
{
	return std::vector<ushort>();
}