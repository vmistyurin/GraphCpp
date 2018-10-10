#include "core/edges/symmetric_edge.hpp"

#include <cassert>
#include <algorithm>

using namespace graphcpp;

SymmetricEdge::SymmetricEdge(msize v1, msize v2, mcontent weight) :
	_v1(std::min(v1, v2)), _v2(std::max(v1, v2)), weight(weight)
{
	assert(v1 != v2);
}

bool SymmetricEdge::operator==(const SymmetricEdge& rhs) const
{
	RETURN_IF(this == &rhs, true);
	return (this->_v1 == rhs._v1) && (this->_v2 == rhs._v2) && (this->weight == rhs.weight);
}

bool SymmetricEdge::operator!=(const SymmetricEdge& right) const
{
	return !(*this == right);
}

msize SymmetricEdge::v1() const
{
	return _v1;
}

msize SymmetricEdge::v2() const
{
	return _v2;
}

std::ostream& graphcpp::operator<< (std::ostream& stream, const SymmetricEdge& edge)
{
	stream << edge.v1() << " " << edge.v2() << edge.weight << std::endl;
	return stream;
}