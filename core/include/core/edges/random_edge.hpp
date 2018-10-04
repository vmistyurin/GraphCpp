#pragma once

#include "core/macroses.hpp"
#include "edge.hpp"

namespace graphcpp
{
    class RandomEdge final
    {
    private:
        Edge _edge;
        double _probability;

    public:
        RandomEdge(Edge edge, double probabitiy);

        bool operator==(const RandomEdge& rhs) const;
        bool operator!=(const RandomEdge& rhs) const;

        msize v1() const;
        msize v2() const;
        mcontent weight() const;
        double probability() const;
    };
}