#include "core/edge.h"
#include <algorithm>
#include <assert.h>

using namespace graphcpp;

Edge::Edge(unsigned int v1, unsigned int v2) noexcept:
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

unsigned int Edge::v1() const noexcept
{
	return _v1;
}
unsigned int Edge::v2() const noexcept
{
	return _v2;
}
