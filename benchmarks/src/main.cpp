#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"
#include "benchmarks/recursive_directory_test_runner.hpp"
#include "core/all.hpp"

using namespace graphcpp_bench;

int main(int argc, char **argv)
{
	std::cout << "Current_path: " << fs::current_path() << std::endl;
	
	RecursiveDirectoryTestRunner tester;

	fs::path path_to_tests = "../../test_generators/graphs";
	fs::path first_answers = "../answers";
	fs::path second_answers = "../answers1";

	tester.run_tests_in_directory(path_to_tests,
		first_answers, 
		Edmonds_Karp_algorithm<graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>>(),
		"Edmonds-Karp");

	tester.run_tests_in_directory(path_to_tests, 
		second_answers,
		Dinic_algorithm<graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>>(), 
		"Dinic");

	std::cout << std::boolalpha;
	std::cout << tester.check_results(first_answers, second_answers) << std::endl;
	
	getchar();
	return 0;
}
