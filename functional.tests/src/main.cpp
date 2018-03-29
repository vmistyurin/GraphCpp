#include "functional.tests/recursive_directory_test_runner.h"	
#include "functional.tests/test_functions.h"
#include "functional.tests/recursive_directory_test_runner.h"
#include "core/matrix_implementation/full_symmetric_matrix.h"
#include "core/matrix_implementation/half_symmetric_matrix.h"
#include "core/graph_implementation/matrix_graph.h"

int main(int argc, char **argv)
{
	graphcpp_bench::RecursiveDirectoryTestRunner tes;

	tes.run_tests_in_directory("../../test_generators/graphs", "../answers", 
		graphcpp_bench::get_test_function_matrix_of_flows<graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>>());

	tes.run_tests_in_directory("../../test_generators/graphs", "../answers1", 
		graphcpp_bench::get_test_function_optimized_matrix_of_flows<graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>>());


	getchar();
	return 0;
}
