#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"

#include "core/utils/system_info.hpp"
#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"
#include "core/flow_calculators/algorithms.hpp"
#include "core/flow_calculators/reduction_use_algorithm.hpp"

using namespace graphcpp;
using namespace graphcpp::flow_calculators;
using namespace graphcpp::bench;

int main(int argc, char** argv)
{
    std::cout << graphcpp::system_info() << std::endl;
	std::cout << "Current_path: " << fs::current_path() << std::endl;

    const fs::path path_to_tests = "../../test_generators/random_graphs";
    const fs::path result_path = "../answers";

    try
    {
        RecursiveDirectoryTestRunner tester(path_to_tests, result_path, std::cout);
        
		single_flow_function_t<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>> func = Edmonds_Karp_algorithm<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>>;
		single_flow_function_t<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>> dinic_func = Dinic_algorithm<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>>;
		single_flow_function_t<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>> preflow_func = preflow_push_algorithm<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>>;

        tester.run_tests(
			factorization<
                RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
            >(func, false),
            "Factorization Edmonds-Karp"
        );

		tester.run_tests(
			factorization<
			RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
			>(func, true),
			"Factorization parallel Edmonds-Karp"
		);

		//tester.run_tests(
		//	factorization<
		//	RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
		//	>(dinic_func, true),
		//	"Factorization Dinic"
		//);

		//tester.run_tests(
		//	factorization<
		//	RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
		//	>(preflow_func, true),
		//	"Factorization preflow_push"
		//);

		/*tester.run_tests(
			reduction_use_algorithm<
				RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
			>(func, true),
			"Factorization with reductions Edmonds-Karp"
		);*/
        
        tester.print_check_result();
    }
    catch (std::exception& error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }
    
	return 0;
}
