#include "gtest/gtest.h"

#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"
#include "core/random_graphs/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/algorithms.hpp"
#include "core/flow_calculators/computations/multi_threaded/multi_thread_calculator.hpp"

namespace graphcpp::testing
{
    // class MultiThreadCalculatorTests : public ::testing::Test
    // {
    // private:
    //     using MatrixType = SingleVectorSymmetricMatrix;
    //     using GraphType = NonOrientedMatrixGraph<MatrixType>;
    //     using RandomGraphType = RandomNonOrientedGraph<GraphType, MatrixType>;

    // protected:
    //     MultiThreadCalculatorTests()
    //     {
    //         std::vector<SymmetricRandomEdge> edges = {
    //             SymmetricRandomEdge(SymmetricEdge(0, 1, 5), 0.3),
    //             SymmetricRandomEdge(SymmetricEdge(0, 3, 6), 0.5),
    //             SymmetricRandomEdge(SymmetricEdge(1, 3, 10), 1),
    //             SymmetricRandomEdge(SymmetricEdge(2, 3, 8), 0.2)
    //         };
    //         auto graph = std::make_unique<RandomGraphType>(edges, 4);
            
    //         const flow_func_t<MatrixType, GraphType> flow_function = std::bind(flow_calculators::matrix_of_flows<MatrixType, GraphType>, std::placeholders::_1, flow_calculators::Edmonds_Karp_algorithm);

    //         calculator = std::make_unique<MultiThreadCalculator<MatrixType, GraphType>>(std::move(graph), flow_function);
    //     }
        
    //     std::unique_ptr<MultiThreadCalculator<>> calculator;
    // };

    // TEST_F(MultiThreadCalculatorTests, ExpectedValueTest)
    // {
    //     std::vector<std::vector<mcontent>> expected_result = {
    //         { 0,    4.5,   0.81, 4.5 },
    //         { 4.5,  0,     1.6,  10.75 },
    //         { 0.81, 1.6,   0,    1.6 },
    //         { 4.5,  10.75, 1.6, 0 }
    //     };
        
    //     const SingleVectorSymmetricMatrix expected_matrix(expected_result);
        
    //     const auto result = this->calculator->expected_value();
        
    //     for (const auto[i, j] : *result)
    //     {
    //         EXPECT_TRUE(are_doubles_equal(result->at(i, j), expected_matrix.at(i, j)));
    //     }
    // }
}