#include "core/edge.hpp"
#include <algorithm>
#include <assert.h>

using namespace graphcpp;

Edge::Edge(msize v1, msize v2, mcontent weight) :
	_v1(std::min(v1, v2)), _v2(std::max(v1, v2)), weight(weight)
{
	assert(v1 != v2);
}

bool Edge::operator==(const Edge& right) const
{
	RETURN_IF(this == &right, true);
	return (this->_v1 == right._v1) && (this->_v2 == right._v2) && (this->weight == right.weight);
}

bool Edge::operator!=(const Edge& right) const
{
	return !(*this == right);
}

msize Edge::v1() const
{
	return _v1;
}

msize Edge::v2() const
{
	return _v2;
}

std::ostream& graphcpp::operator<< (std::ostream& stream, const Edge& edge)
{
	stream << edge.v1() << " " << edge.v2() << edge.weight << std::endl;
	return stream;
}