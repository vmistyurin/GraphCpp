#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"

#include "core/all.hpp"

using namespace graphcpp_bench;

int main(int argc, char **argv)
{
	std::cout << "Current_path: " << fs::current_path() << std::endl;
	
	RecursiveDirectoryTestRunner tester;

	const fs::path path_to_tests = "../../test_generators/graphs";
	const fs::path first_answers = "../answers";
	const fs::path second_answers = "../answers1";

	tester.run_tests_in_directory(path_to_tests,
		first_answers, 
		preflow_push_algorithm<graphcpp::NonOrientedMatrixGraph<graphcpp::FullSymmetricMatrix>>(),
		"Preflow-push");

	tester.run_tests_in_directory(path_to_tests, 
		second_answers,
		Edmonds_Karp_algorithm<graphcpp::NonOrientedMatrixGraph<graphcpp::FullSymmetricMatrix>>(), 
		"Edmonds-Karp");

	if (auto differences = tester.check_results(first_answers, second_answers); differences.empty())
	{
		std::cout << "No differences" << std::endl;
	}
	else
	{
		std::cout << "There is " << differences.size() << " differences" << std::endl;
		for (const auto& path : differences)
		{
			std::cout << path.string() << std::endl;
		}
	}
	
	getchar();
	return 0;
}
