#pragma once

#include <functional>
#include <memory>

namespace graphcpp
{
    class SymmetricMatrixBase;
    class NonOrientedGraphBase;
}

namespace graphcpp::flow_calculators
{
    std::unique_ptr<SymmetricMatrixBase> calculate_flows_in_tree(const NonOrientedGraphBase& graph);
}

