#include "gtest/gtest.h"

#include "core/flow_calculators/flow_helpers.hpp"

#include "unit_tests/utils/comparators.hpp"
#include "unit_tests/implementations.hpp"

namespace graphcpp::testing
{
    template<class NorGraphType>
    class FlowHelpersTests : public ::testing::Test // TODO: add test to matrix_of_flows
    {    
    };

    TYPED_TEST_CASE(FlowHelpersTests, NonOrientedGraphImplementations,);

    TYPED_TEST(FlowHelpersTests, FlowsInTreeTest)
    {
        const std::vector<SymmetricEdge> edges = {
            SymmetricEdge(0, 3, 8),
            SymmetricEdge(3, 1, 5),
            SymmetricEdge(1, 4, 25),
            SymmetricEdge(1, 5, 3),
            SymmetricEdge(1, 7, 10),
            SymmetricEdge(7, 6, 1),
            SymmetricEdge(7, 2, 20)
        };
        TypeParam tree(edges, 8);
        
        FullSymmetricMatrix expected_flows({
            { 0, 5, 5, 8, 5, 3, 1, 5 },
            { 5, 0, 10, 5, 25, 3, 1, 10 },
            { 5, 10, 0, 5, 10, 3, 1, 20 },
            { 8, 5, 5, 0, 5, 3, 1, 5 },
            { 5, 25, 10, 5, 0, 3, 1, 10 },
            { 3, 3, 3, 3, 3, 0, 1, 3 },
            { 1, 1, 1, 1, 1, 1, 0, 1 },
            { 5, 10, 20, 5, 10, 3, 1, 0 }
        });
        
        auto flows = flow_calculators::calculate_flows_in_tree<FullSymmetricMatrix>(tree);

        EXPECT_EQ(flows, expected_flows);
    }

    TYPED_TEST(FlowHelpersTests, OneDimensionGraphFlowsTest)
    {
        TypeParam graph({}, 1);
        
		FullSymmetricMatrix expected_flows(1);

        auto flows = flow_calculators::calculate_for_small_graph<FullSymmetricMatrix>(graph);

        EXPECT_EQ(flows, expected_flows);
    }

    TYPED_TEST(FlowHelpersTests, TwoDimensionGraphFlowsTest)
    {
        TypeParam graph({ SymmetricEdge(0, 1, 5) }, 2);
        
        FullSymmetricMatrix expected_flows({
            { 0, 5 },
            { 5, 0 }
        });
        
        auto flows = flow_calculators::calculate_for_small_graph<FullSymmetricMatrix>(graph);

        EXPECT_EQ(flows, expected_flows);
    }

    TYPED_TEST(FlowHelpersTests, ThreeDimensionGraphFlowsTest)
    {
        const std::vector<SymmetricEdge> edges = {
            SymmetricEdge(0, 1, 5),
            SymmetricEdge(0, 2, 7),
            SymmetricEdge(1, 2, 3)
        };
        TypeParam graph(edges, 3);

        FullSymmetricMatrix expected_flows({
            { 0, 8, 10 },
            { 8, 0, 8 },
            { 10, 8, 0 }
        });
        
        auto flows = flow_calculators::calculate_for_small_graph<FullSymmetricMatrix>(graph);

        EXPECT_EQ(flows, expected_flows);
    }

    // TYPED_TEST(FlowHelpersTests, FourDimensionGraphFlowsTest) // TODO: Add test for 4 dimensional matrix
    // {
    //     const std::vector<SymmetricEdge> edges = {
    //         SymmetricEdge(0, 1, 5),
    //         SymmetricEdge(0, 2, 7),
    //         SymmetricEdge(1, 2, 3)
    //     };
    //     TypeParam graph(edges, 3);

    //     FullSymmetricMatrix expected_flows({
    //         { 0, 8, 10 },
    //         { 8, 0, 8 },
    //         { 10, 8, 0 }
    //     });
        
    //     auto flows = flow_calculators::calculate_for_small_graph<FullSymmetricMatrix>(graph);

    //     EXPECT_EQ(flows, expected_flows);
    // }
}
