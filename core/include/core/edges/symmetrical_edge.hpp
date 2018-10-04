#ifndef GRAPH_CORE_SYMMETRICAL_EDGE_HPP
#define GRAPH_CORE_SYMMETRICAL_EDGE_HPP

#include <ostream>

#include "core/macroses.hpp"

namespace graphcpp
{
	class SymmetricalEdge final
	{
	private:
		msize _v1, _v2;

	public:
		SymmetricalEdge(msize v1, msize v2, mcontent weight);

		bool operator==(const SymmetricalEdge& rhs) const;
		bool operator!=(const SymmetricalEdge& rhs) const;

		msize v1() const;
		msize v2() const;

        mcontent weight;
	};

	std::ostream& operator<< (std::ostream& stream, const SymmetricalEdge& edge);
}
#endif