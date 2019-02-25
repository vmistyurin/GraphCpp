#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"

#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"
#include "core/flow_calculators/flow_calculators.hpp"

using namespace graphcpp;
using namespace graphcpp_bench;

int main(int argc, char** argv)
{
	std::cout << "Current_path: " << fs::current_path() << std::endl;
    
	const fs::path path_to_tests = "../../test_generators/random_graphs";
	const fs::path result_path = "../answers";
    
    try
    {
        RecursiveDirectoryTestRunner tester(path_to_tests, result_path, std::cout);
        
        tester.run_tests(
            multi_threaded_matrix_of_flows<
                RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
            >(flow_calculators::Edmonds_Karp_algorithm),
            "Multi thread Edmons-Karp"
        );
        
        std::function<SingleVectorSymmetricMatrix(const NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>&)> func = std::bind(flow_calculators::reduction_use_algorithm_de<
            NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix
        >, std::placeholders::_1, flow_calculators::Edmonds_Karp_algorithm);

        tester.run_tests(
            multi_threaded_matrix_of_flows(std::move(func)),
            "Multi thread reduction de use"
        );
        
        tester.print_check_result();
    }
    catch (std::exception& error)
    {
        std::cout << error.what() << std::endl;
    }
    
	return 0;
}
