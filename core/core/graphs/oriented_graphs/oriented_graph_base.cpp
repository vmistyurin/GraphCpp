#include "core/graphs/oriented_graphs/oriented_graph_base.hpp"

using namespace graphcpp;

MatrixIterator OrientedGraphBase::begin() const
{
	return MatrixIterator(dimension());
}

MatrixIterator OrientedGraphBase::end() const
{
	return MatrixIterator();
}