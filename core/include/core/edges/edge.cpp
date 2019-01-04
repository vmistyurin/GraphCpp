#include "core/edges/edge.hpp"

using namespace graphcpp;

Edge::Edge(msize v1, msize v2, mcontent weight) :
	_v1(v1), _v2(v2), weight(weight)
{
}

bool Edge::operator==(const Edge& rhs) const
{
	RETURN_IF(this == &rhs, true);
	return _v1 == rhs.v1() && _v2 == rhs.v2() && weight == rhs.weight;
}

bool Edge::operator!=(const Edge& rhs) const
{
	return !(*this == rhs);
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
	stream << edge.v1() << " " << edge.v2() << " " << edge.weight;
	return stream;
}
