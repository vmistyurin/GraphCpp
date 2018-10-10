#ifndef GRAPH_CORE_SYMMETRICAL_EDGE_HPP
#define GRAPH_CORE_SYMMETRICAL_EDGE_HPP

#include <ostream>

#include "core/macroses.hpp"

namespace graphcpp
{
	class SymmetricEdge final
	{
	private:
		msize _v1, _v2;

	public:
		SymmetricEdge(msize v1, msize v2, mcontent weight);

		bool operator==(const SymmetricEdge& rhs) const;
		bool operator!=(const SymmetricEdge& rhs) const;

		msize v1() const;
		msize v2() const;

        mcontent weight;
	};

	std::ostream& operator<< (std::ostream& stream, const SymmetricEdge& edge);
}
#endif