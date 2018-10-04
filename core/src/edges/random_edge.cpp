#include "core/edges/random_edge.hpp"

using namespace graphcpp;

RandomEdge::RandomEdge(Edge edge, double probabitiy) :
    _edge(edge), _probability(probabitiy)
{
}

bool RandomEdge::operator==(const RandomEdge& rhs) const
{
    RETURN_IF(this == &rhs, true);
    return _edge == rhs._edge && _probability == rhs._probability;
}

bool RandomEdge::operator!=(const RandomEdge& rhs) const
{
    return !(*this == rhs);
}

msize RandomEdge::v1() const
{
    return _edge.v1();
}

msize RandomEdge::v2() const
{
    return _edge.v2();
}

mcontent RandomEdge::weight() const
{
    return _edge.weight;
}

double RandomEdge::probability() const
{
    return _probability;
}