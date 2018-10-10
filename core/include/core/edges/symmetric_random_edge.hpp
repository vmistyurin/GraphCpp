#pragma once

#include "core/macroses.hpp"
#include "core/edges/symmetric_edge.hpp"

namespace graphcpp
{
    class SymmetricRandomEdge final
    {
    private:
        SymmetricEdge _edge;
        double _probability;

    public:
        SymmetricRandomEdge(SymmetricEdge edge, double probability);

        bool operator==(const SymmetricRandomEdge& rhs) const;
        bool operator!=(const SymmetricRandomEdge& rhs) const;

        msize v1() const;
        msize v2() const;
        mcontent weight() const;
        double probability() const;
    };
}