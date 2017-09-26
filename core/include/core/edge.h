#ifndef GRAPH_CORE_EDGE_H
#define GRAPH_CORE_EDGE_H

#include "macroses.h"

namespace graphcpp
{
	class Edge
	{
	private:
		ushort _v1, _v2;

	public:
		Edge(ushort v1, ushort v2) noexcept;

		Edge(const Edge&) = delete;
		Edge operator=(const Edge&) = delete;

		bool operator==(const Edge& right) const noexcept;
		bool operator!=(const Edge& right) const noexcept;

		ushort v1() const noexcept;
		ushort v2() const noexcept;
	};
}
#endif