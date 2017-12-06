#ifndef GRAPH_CORE_EDGE_H
#define GRAPH_CORE_EDGE_H

#include "macroses.h"

namespace graphcpp
{
	class Edge
	{
	private:
		msize _v1, _v2;
        mcontent _weight;
	public:
		Edge(msize v1, msize v2, mcontent weight);

		//Edge(const Edge&) = delete;
		//Edge operator=(const Edge&) = delete;

		bool operator==(const Edge& right) const;
		bool operator!=(const Edge& right) const;

		msize v1() const;
		msize v2() const;
        mcontent weight() const;
	};
}
#endif