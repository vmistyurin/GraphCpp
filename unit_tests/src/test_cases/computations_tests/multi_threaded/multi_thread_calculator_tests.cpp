#include "gtest/gtest.h"

#include "core/all.hpp"

using namespace graphcpp;

class MultiThreadCalculatorTests : public ::testing::Test
{
protected:
    MultiThreadCalculatorTests()
    {
        std::vector<SymmetricRandomEdge> edges = {
            SymmetricRandomEdge(SymmetricEdge(0, 1, 5), 0.3),
            SymmetricRandomEdge(SymmetricEdge(0, 3, 6), 0.5),
            SymmetricRandomEdge(SymmetricEdge(1, 3, 10), 1),
            SymmetricRandomEdge(SymmetricEdge(2, 3, 8), 0.2)
        };
        auto graph = std::make_unique<RandomNonOrientedGraph<NonOrientedMatrixGraph<FullSymmetricMatrix>, FullSymmetricMatrix>>(edges, 4);
        
        calculator = std::make_unique<MultiThreadCalculator>(std::move(graph),
            std::bind(flow_calculators::matrix_of_flows, std::placeholders::_1, flow_calculators::Edmonds_Karp_algorithm)
        );
    }
    
    std::unique_ptr<MultiThreadCalculator> calculator;
};

TEST_F(MultiThreadCalculatorTests, ExpectedValueTest)
{
    std::vector<std::vector<mcontent>> expected_result = {
        { 0,    4.5,   0.81, 4.5 },
        { 4.5,  0,     1.6,  10.75 },
        { 0.81, 1.6,   0,    1.6 },
        { 4.5,  10.75, 1.6, 0 }
    };
    
    const FullSymmetricMatrix expected_matrix(expected_result);
    
    const auto result = this->calculator->expected_value();
    
    for (const auto[i, j] : *result)
    {
        EXPECT_TRUE(are_doubles_equal(result->at(i, j), expected_matrix.at(i, j)));
    }
}
