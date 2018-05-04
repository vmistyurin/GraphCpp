#include "core/symmetrical_edge.hpp"

#include <cassert>
#include <algorithm>

using namespace graphcpp;

SymmetricalEdge::SymmetricalEdge(msize v1, msize v2, mcontent weight) :
	_v1(std::min(v1, v2)), _v2(std::max(v1, v2)), weight(weight)
{
	assert(v1 != v2);
}

bool SymmetricalEdge::operator==(const SymmetricalEdge& rhs) const
{
	RETURN_IF(this == &rhs, true);
	return (this->_v1 == rhs._v1) && (this->_v2 == rhs._v2) && (this->weight == rhs.weight);
}

bool SymmetricalEdge::operator!=(const SymmetricalEdge& right) const
{
	return !(*this == right);
}

msize SymmetricalEdge::v1() const
{
	return _v1;
}

msize SymmetricalEdge::v2() const
{
	return _v2;
}

std::ostream& graphcpp::operator<< (std::ostream& stream, const SymmetricalEdge& edge)
{
	stream << edge.v1() << " " << edge.v2() << edge.weight << std::endl;
	return stream;
}