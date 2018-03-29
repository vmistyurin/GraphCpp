#ifndef FUNCTIONAL_TESTS_RECURSIVE_DIRECTORY_TEST_RUNNER_H
#define FUNCTIONAL_TESTS_RECURSIVE_DIRECTORY_TEST_RUNNER_H

#include <boost/filesystem.hpp>
#include <functional>
#include <chrono>

namespace graphcpp_bench
{
	namespace fs = boost::filesystem;

	class RecursiveDirectoryTestRunner final 
	{
	public:
		std::chrono::milliseconds run_single_test(const fs::path& path_to_test, const fs::path& path_to_answer,
			const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent = 0);

		void run_tests_in_directory(const fs::path& path_to_directory, const fs::path& path_to_answers, 
			const std::function<std::string(std::ifstream&&)>& test_function);
	private:
		void run_tests_in_directory_uncheked(const fs::path& path_to_directory, const fs::path& path_to_answers, 
			const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent);
	};

	
}
#endif