#ifndef GRAPH_CORE_MATRIX_GRAPH_H
#define GRAPH_CORE_MATRIX_GRAPH_H

#include "core/graph_base.h"
#include "core/macroses.h"

namespace graphcpp
{
	class SymmetricMatrixGraph : public GraphBase
	{
	private:
		std::vector<std::vector<bool>> _matrix;
	public:
		SymmetricMatrixGraph(const std::vector<Edge>& edges, ushort dimension);
		//SymmetricMatrixGraph(const std::vector<std::vector<bool>>& matrix);

		ushort Dimension() const noexcept override;

		std::vector<std::vector<bool>> GetMatrix() const noexcept override;
		std::vector<Edge> GetEdges() const noexcept override;
		std::vector<ushort> GetLinkedVertexes(ushort vertex) const noexcept override;
	};
}
#endif