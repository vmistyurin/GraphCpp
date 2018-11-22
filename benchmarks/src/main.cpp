#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"

#include "core/all.hpp"

using namespace graphcpp;
using namespace graphcpp_bench;

int main(int argc, char **argv)
{
	std::cout << "Current_path: " << fs::current_path() << std::endl;
    
	const fs::path path_to_tests = "../../../test_generators/random_graphs";
	const fs::path first_answers = "../answers";
	const fs::path second_answers = "../answers1";
    
    RecursiveDirectoryTestRunner tester(path_to_tests, std::cout);

    tester.run_tests_in_directory(
        first_answers,
        single_threaded_matrix_of_flows<
            RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
        >(flow_calculators::Edmonds_Karp_algorithm),
        "Single thread"
    );
    
	tester.run_tests_in_directory(
		second_answers,
        multi_threaded_matrix_of_flows<
            RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
        >(flow_calculators::Edmonds_Karp_algorithm),
        "Multi thread"
    );

    tester.print_check_result(first_answers, second_answers);

	return 0;
}
