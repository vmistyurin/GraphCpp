#include "gtest/gtest.h"

#include "core/flow_calculators/algorithms.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/reduction_use_factorization.hpp"

#include "unit_tests/test_data/non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

namespace graphcpp::testing
{
    template<class SymMatrixType>
    class ReductionUseFactorizationTests : public ::testing::Test
    {
    private:
        using MatrixType = SymMatrixType;
        using GraphType = NonOrientedMatrixGraph<MatrixType>;
        using RandomGraphType = RandomNonOrientedGraph<GraphType, MatrixType>;
        
    protected:
        ReductionUseFactorizationTests()
        {
            _flow_function = std::bind(flow_calculators::matrix_of_flows<MatrixType, GraphType>, std::placeholders::_1, flow_calculators::Edmonds_Karp_algorithm<GraphType>);
        }
        
        RandomGraphType _graph = []{
            std::vector<SymmetricRandomEdge> edges = {
                SymmetricRandomEdge(SymmetricEdge(0, 1, 5), 0.3),
                SymmetricRandomEdge(SymmetricEdge(0, 3, 6), 0.5),
                SymmetricRandomEdge(SymmetricEdge(1, 3, 10), 1),
                SymmetricRandomEdge(SymmetricEdge(2, 3, 8), 0.2)
            };
            return RandomGraphType(edges, 4);
        }();
        flow_func_t<MatrixType, GraphType> _flow_function;
    };
    
    TYPED_TEST_CASE(ReductionUseFactorizationTests, SymmetricMatrixImplementations,);
    
    TYPED_TEST(ReductionUseFactorizationTests, WithEdmondsKarpAlgorithm)
    {
        const std::vector<std::vector<mcontent>> expected_result = {
            { 0,    4.5,   0.81, 4.5 },
            { 4.5,  0,     1.6,  10.75 },
            { 0.81, 1.6,   0,    1.6 },
            { 4.5,  10.75, 1.6, 0 }
        };
        const SingleVectorSymmetricMatrix expected_matrix(expected_result);

        single_flow_function_t<NonOrientedMatrixGraph<TypeParam>> single_calc = flow_calculators::Edmonds_Karp_algorithm<NonOrientedMatrixGraph<TypeParam>>;
        
        const auto actual_flows = flow_calculators::reduction_use_factorization(
            this->_graph,
            std::move(single_calc),
            nullptr,
            false
        );
        
        ASSERT_EQ(actual_flows.dimension(), expected_matrix.dimension());
        for (const auto [i, j] : actual_flows)
        {
            EXPECT_TRUE(are_doubles_equal(actual_flows.at(i, j), expected_matrix.at(i, j)));
        }
    }
//
//    TYPED_TEST(ReductionUseAlgorithmTests, WithDinicAlgorithm)
//    {
//        const auto actual_flows = flow_calculators::reduction_use_algorithm<TypeParam, FullSymmetricMatrix>(
//                                                                                                            this->test_graph,
//                                                                                                            flow_calculators::Dinic_algorithm<TypeParam>,
//                                                                                                            nullptr
//                                                                                                            );
//
//        EXPECT_EQ(this->expected_flows, actual_flows);
//    }
//
//    TYPED_TEST(ReductionUseAlgorithmTests, WithPreflowPushAlgorithm)
//    {
//        const auto actual_flows = flow_calculators::reduction_use_algorithm<TypeParam, HalfSymmetricMatrix>(
//                                                                                                            this->test_graph,
//                                                                                                            flow_calculators::preflow_push_algorithm<TypeParam>,
//                                                                                                            nullptr
//                                                                                                            );
//
//        EXPECT_EQ(this->expected_flows, actual_flows);
//    }
}
