#include "gtest/gtest.h"

#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"
#include "core/random_graphs/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/algorithms.hpp"
#include "core/flow_calculators/factorization.hpp"

namespace graphcpp::testing
{
    class FactorizationTests : public ::testing::Test
    {
    private:
        using MatrixType = SingleVectorSymmetricMatrix;
        using GraphType = NonOrientedMatrixGraph<MatrixType>;
        using RandomGraphType = RandomNonOrientedGraph<GraphType, MatrixType>;

    protected:
        FactorizationTests()
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

    TEST_F(FactorizationTests, SingleThreadFactorizationTest)
    {
        std::vector<std::vector<mcontent>> expected_result = {
            { 0,    4.5,   0.81, 4.5 },
            { 4.5,  0,     1.6,  10.75 },
            { 0.81, 1.6,   0,    1.6 },
            { 4.5,  10.75, 1.6, 0 }
        };
        const SingleVectorSymmetricMatrix expected_matrix(expected_result);
        
        const auto result = flow_calculators::factorize(this->_graph, this->_flow_function, false);
        
        for (const auto[i, j] : result)
        {
            EXPECT_TRUE(are_doubles_equal(result.at(i, j), expected_matrix.at(i, j)));
        }
    }

	TEST_F(FactorizationTests, MultiThreadFactorizationTest)
	{
		std::vector<std::vector<mcontent>> expected_result = {
			{ 0,    4.5,   0.81, 4.5 },
			{ 4.5,  0,     1.6,  10.75 },
			{ 0.81, 1.6,   0,    1.6 },
			{ 4.5,  10.75, 1.6, 0 }
		};
		const SingleVectorSymmetricMatrix expected_matrix(expected_result);

		const auto result = flow_calculators::factorize(this->_graph, this->_flow_function, true);

		for (const auto [i, j] : result)
		{
			EXPECT_TRUE(are_doubles_equal(result.at(i, j), expected_matrix.at(i, j)));
		}
	}
}