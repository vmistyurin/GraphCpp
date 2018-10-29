#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"

#include "core/all.hpp"

using namespace graphcpp_bench;

int main(int argc, char **argv)
{
	std::cout << "Current_path: " << fs::current_path() << std::endl;
	
	RecursiveDirectoryTestRunner tester;

	const fs::path path_to_tests = "../../test_generators/random_graphs";
	const fs::path first_answers = "../answers";
	const fs::path second_answers = "../answers1";
	const fs::path third_answers = "../answers2";
    
	tester.run_tests_in_directory(path_to_tests,
		first_answers,
        single_threaded_matrix_of_flows<
            graphcpp::RandomNonOrientedGraph<graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>, graphcpp::HalfSymmetricMatrix>
        >
            (std::bind(graphcpp::flow_calculators::matrix_of_flows, std::placeholders::_1, graphcpp::flow_calculators::Edmonds_Karp_algorithm)),
		"Single thread");

	tester.run_tests_in_directory(path_to_tests, 
		second_answers,
        multi_threaded_matrix_of_flows<
            graphcpp::RandomNonOrientedGraph<graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>, graphcpp::HalfSymmetricMatrix>
        >
            (std::bind(graphcpp::flow_calculators::matrix_of_flows, std::placeholders::_1, graphcpp::flow_calculators::Edmonds_Karp_algorithm)),
        "Multi thread");

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

	return 0;
}
