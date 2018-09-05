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
	const fs::path third_answers = "../answers2";

	tester.run_tests_in_directory(path_to_tests,
		first_answers, 
		reduction_use_algorithm<graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>>(graphcpp::flow_calculators::Edmonds_Karp_algorithm),
		"Edmonds-Karp");

	tester.run_tests_in_directory(path_to_tests, 
		second_answers,
		reduction_use_algorithm<graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>>(graphcpp::flow_calculators::Dinic_algorithm), 
		"Dinic");

	tester.run_tests_in_directory(path_to_tests,
		third_answers,
		reduction_use_algorithm<graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>>(graphcpp::flow_calculators::preflow_push_algorithm),
		"preflow_push");

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
