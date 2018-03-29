#include "benchmarks/recursive_directory_test_runner.h"	
#include "benchmarks/test_functions.h"
#include "benchmarks/recursive_directory_test_runner.h"
#include "core/matrix_implementation/full_symmetric_matrix.h"
#include "core/matrix_implementation/half_symmetric_matrix.h"
#include "core/graph_implementation/matrix_graph.h"

using namespace graphcpp_bench;

int main(int argc, char **argv)
{
	std::cout << "Current_path: " << fs::current_path() << std::endl;

	RecursiveDirectoryTestRunner tester;

	tester.run_tests_in_directory("../../test_generators/graphs", "../answers", 
		get_test_function_matrix_of_flows<graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>>());

	tester.run_tests_in_directory("../../test_generators/graphs", "../answers1", 
		get_test_function_optimized_matrix_of_flows<graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>>());


	getchar();
	return 0;
}
