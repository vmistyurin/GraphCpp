#ifndef GRAPH_CORE_GRAPHBASE_H
#define GRAPH_CORE_GRAPHBASE_H
#include "core/edge.h"
#include <vector>

namespace graphcpp
{
	struct GraphBase
	{
		virtual std::vector<std::vector<bool>> GetMatrix() const noexcept = 0;
		virtual std::vector<Edge> GetEdges() const noexcept = 0;
		virtual unsigned int Dimension() const noexcept = 0;
		virtual std::vector<int> GetLinkedVertexes(unsigned int vertex) const noexcept  = 0;
	};
}
#endif