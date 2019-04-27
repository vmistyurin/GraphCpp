#include "benchmarks/recursive_directory_test_runner.hpp"	
#include "benchmarks/test_functions.hpp"

#include "core/utils/system_info.hpp"
#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"
#include "core/flow_calculators/algorithms.hpp"
#include "core/flow_calculators/reduction_use_algorithm.hpp"

using namespace graphcpp;
using namespace graphcpp::flow_calculators;
using namespace graphcpp::bench;

int main(int argc, char** argv)
{
    std::cout << graphcpp::system_info() << std::endl;
	std::cout << "Current_path: " << fs::current_path() << std::endl;

    const fs::path path_to_tests = "../../test_generators/random_graphs";
    const fs::path result_path = "../answers";

    try
    {
        RecursiveDirectoryTestRunner tester(path_to_tests, result_path, std::cout);
        
        // tester.run_tests(
        //     multi_threaded_matrix_of_flows<
        //         RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
        //     >(flow_calculators::Edmonds_Karp_algorithm),
        //     "Multi thread Edmonds-Karp"
        // );

        // std::function<SingleVectorSymmetricMatrix(const NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>&, ReductionStats*)> func_d = std::bind(flow_calculators::reduction_use_algorithm<
        //     NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix
        // >, std::placeholders::_1, flow_calculators::Edmonds_Karp_algorithm, std::placeholders::_2);

        // tester.run_tests(
        //     multi_threaded_matrix_of_flows(std::move(func_d)),
        //     "Multi thread reduction use functional"
        // );
        
        tester.print_check_result();
    }
    catch (std::exception& error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }
    
	return 0;
}
