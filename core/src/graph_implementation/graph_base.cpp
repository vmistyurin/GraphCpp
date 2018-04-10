#include "core/graph_implementation/graph_base.hpp"

using namespace graphcpp;

SymmetricMatrixIterator GraphBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator GraphBase::end() const
{
	return SymmetricMatrixIterator();
}