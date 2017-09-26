#include "core/edge.h"
#include <algorithm>
#include <assert.h>

using namespace graphcpp;

Edge::Edge(ushort v1, ushort v2) noexcept:
	_v1(std::min(v1, v2)), _v2(std::max(v1, v2)) 
{
	assert(v1 != v2);
}

bool Edge::operator==(const Edge& right) const noexcept
{
	assert(this->_v1 < this->_v2);
	return (this->_v1 == right._v1) && (this->_v2 == right._v2);
}

bool Edge::operator!=(const Edge& right) const noexcept
{
	return !(*this == right);
}

ushort Edge::v1() const noexcept
{
	return _v1;
}
ushort Edge::v2() const noexcept
{
	return _v2;
}
