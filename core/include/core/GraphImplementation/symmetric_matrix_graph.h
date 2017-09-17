#ifndef GRAPH_CORE_MATRIX_GRAPH_H
#define GRAPH_CORE_MATRIX_GRAPH_H

#include "core/graph_base.h"
namespace graphcpp
{
	class SymmetricMatrixGraph : public GraphBase
	{
	private:
		std::vector<std::vector<bool>> _matrix;
	public:
		SymmetricMatrixGraph(const std::vector<Edge>& edges, unsigned int dimension);
		//SymmetricMatrixGraph(const std::vector<std::vector<bool>>& matrix);

		unsigned int Dimension() const noexcept override;

		std::vector<std::vector<bool>> GetMatrix() const noexcept override;
		std::vector<Edge> GetEdges() const noexcept override;
		std::vector<int> GetLinkedVertexes(unsigned int vertex) const noexcept override;
	};
}
#endif