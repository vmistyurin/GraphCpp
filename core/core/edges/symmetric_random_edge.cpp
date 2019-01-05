#include "core/edges/symmetric_random_edge.hpp"

#include <cassert>

#include "core/utils/numeric.hpp"

using namespace graphcpp;

SymmetricRandomEdge::SymmetricRandomEdge(SymmetricEdge edge, double probability) :
    _edge(edge), _probability(probability)
{
    assert(probability > 0);
    assert(probability <= 1);
}

bool SymmetricRandomEdge::operator==(const SymmetricRandomEdge& rhs) const
{
    RETURN_IF(this == &rhs, true);
    return _edge == rhs._edge && are_doubles_equal(_probability, rhs._probability);
}

bool SymmetricRandomEdge::operator!=(const SymmetricRandomEdge& rhs) const
{
    return !(*this == rhs);
}

msize SymmetricRandomEdge::v1() const
{
    return _edge.v1();
}

msize SymmetricRandomEdge::v2() const
{
    return _edge.v2();
}

mcontent SymmetricRandomEdge::weight() const
{
    return _edge.weight;
}

double SymmetricRandomEdge::probability() const
{
    return _probability;
}
