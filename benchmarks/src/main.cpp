#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"

#include "core/all.hpp"

using namespace graphcpp;
using namespace graphcpp_bench;

int main(int argc, char** argv)
{
	std::cout << "Current_path: " << fs::current_path() << std::endl;
    
	const fs::path path_to_tests = "../../../test_generators/random_graphs";
	const fs::path result_path = "../answers";
    
    try
    {
        RecursiveDirectoryTestRunner tester(path_to_tests, result_path, std::cout);
        
        tester.run_tests(
            single_threaded_matrix_of_flows<
                RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
            >(flow_calculators::Edmonds_Karp_algorithm),
            "Single thread"
        );
        
        tester.run_tests(
            multi_threaded_matrix_of_flows<
                RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
            >(flow_calculators::Edmonds_Karp_algorithm),
            "Multi thread"
        );
        
        tester.print_check_result();
    }
    catch (std::exception& error)
    {
        std::cout << error.what() << std::endl;
    }
    
	return 0;
}
