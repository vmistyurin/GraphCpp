#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"
#include "benchmarks/recursive_directory_test_runner.hpp"
#include "core/matrix_implementation/full_symmetric_matrix.hpp"
#include "core/matrix_implementation/half_symmetric_matrix.hpp"
#include "core/graph_implementation/matrix_graph.hpp"

using namespace graphcpp_bench;

int main(int argc, char **argv)
{
	std::cout << "Current_path: " << fs::current_path() << std::endl;
	
	RecursiveDirectoryTestRunner tester;

	fs::path path_to_tests = "../../test_generators/graphs";
	fs::path first_answers = "../answers";
	fs::path second_answers = "../answers1";

	tester.run_tests_in_directory(path_to_tests, first_answers, 
		get_test_function_matrix_of_flows<graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>>(), "Non optimized FullSymmetricMatrix");

	tester.run_tests_in_directory(path_to_tests, second_answers,
		get_test_function_optimized_matrix_of_flows<graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>>(), "Optimized FullSymmetricMatrix");

	std::cout << std::boolalpha;
	std::cout << tester.check_results(first_answers, second_answers) << std::endl;
	
	getchar();
	return 0;
}
