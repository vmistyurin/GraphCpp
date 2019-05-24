#include "gtest/gtest.h"

#include "unit_tests/implementations.hpp"
#include "unit_tests/utils/comparators.hpp"

namespace graphcpp::testing
{
    template<class NorGraphType>
    class NonOrientedGraphBaseHelpersTests : public ::testing::Test
    {
    protected:
        NonOrientedGraphBaseHelpersTests()
        {
        }
    };
    
    TYPED_TEST_CASE(NonOrientedGraphBaseHelpersTests, NonOrientedGraphImplementations,);
    
    TYPED_TEST(NonOrientedGraphBaseHelpersTests, HingesTest)
    {
        std::vector<SymmetricEdge> edges = {
            SymmetricEdge(0, 7, 1),
            SymmetricEdge(7, 5, 1),
            
            SymmetricEdge(1, 6, 1),
            SymmetricEdge(1, 4, 1),
            SymmetricEdge(4, 6, 1),
            SymmetricEdge(2, 3, 1),
            SymmetricEdge(3, 4, 1),
            SymmetricEdge(2, 4, 1)
        };
        
        const auto graph = TypeParam(edges, 8);
        
        const auto hinges = get_hinges(graph);
        
        EXPECT_TRUE(compare_without_order(hinges, {4, 7 }));
    }
}

