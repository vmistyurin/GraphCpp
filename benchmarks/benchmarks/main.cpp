#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"

#include "core/utils/system_info.hpp"
#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"
#include "core/flow_calculators/algorithms.hpp"
#include "core/flow_calculators/flow_calculators.hpp"

using namespace graphcpp;
using namespace graphcpp::bench;

int main(int argc, char** argv)
{
    std::cout << graphcpp::system_info() << std::endl;
	std::cout << "Current_path: " << fs::current_path() << std::endl;
    
    #ifdef _WIN32
	    const fs::path path_to_tests = "../../../test_generators/random_graphs";
	    const fs::path result_path = "../../answers";
    #else
    	const fs::path path_to_tests = "../../test_generators/random_graphs";
	    const fs::path result_path = "../answers";
    #endif

    try
    {
        RecursiveDirectoryTestRunner tester(path_to_tests, result_path, std::cout);
        
        // tester.run_tests(
        //     multi_threaded_matrix_of_flows<
        //         RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
        //     >(flow_calculators::Edmonds_Karp_algorithm),
        //     "Multi thread Edmons-Karp"
        // );

        std::function<SingleVectorSymmetricMatrix(const NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>&)> func_d = std::bind(flow_calculators::reduction_use_algorithm_d<
            NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix
        >, std::placeholders::_1, flow_calculators::Edmonds_Karp_algorithm);

        tester.run_tests(
            multi_threaded_matrix_of_flows(std::move(func_d)),
            "Multi thread reduction use functional"
        );
        
        tester.print_check_result();
    }
    catch (std::exception& error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }
    
	return 0;
}
