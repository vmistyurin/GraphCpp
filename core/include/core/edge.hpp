#ifndef GRAPH_CORE_EDGE_H
#define GRAPH_CORE_EDGE_H

#include "core/macroses.hpp"

namespace graphcpp
{
	class Edge final
	{
	private:
		msize _v1, _v2;

	public:
		Edge(msize v1, msize v2, mcontent weight);

		bool operator==(const Edge& right) const;
		bool operator!=(const Edge& right) const;

		msize v1() const;
		msize v2() const;

        mcontent weight;
	};
}
#endif