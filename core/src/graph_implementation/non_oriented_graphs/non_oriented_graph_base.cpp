#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"

using namespace graphcpp;

SymmetricMatrixIterator NonOrientedGraphBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator NonOrientedGraphBase::end() const
{
	return SymmetricMatrixIterator();
}