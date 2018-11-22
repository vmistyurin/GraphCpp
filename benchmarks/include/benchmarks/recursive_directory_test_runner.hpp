#pragma once

#include <chrono>

#include <boost/filesystem.hpp>

namespace graphcpp_bench
{
	namespace fs = boost::filesystem;

	class RecursiveDirectoryTestRunner final 
	{
    private:
        fs::path _path_to_tests;
        std::ostream& _logger;
        
	public:
        explicit RecursiveDirectoryTestRunner(fs::path path_to_tests, std::ostream& logger);
        
		std::chrono::milliseconds run_single_test(const fs::path& path_to_test, const fs::path& path_to_answer,
			const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent = 0);

		void run_tests_in_directory(const fs::path& path_to_answers, 
			const std::function<std::string(std::ifstream&&)>& test_function, std::string_view test_name);

		std::list<fs::path> check_results(const fs::path& first_answers, const fs::path& second_answers);
        void print_check_result(const fs::path& first_answers, const fs::path& second_answers);

	private:
		void run_tests_in_directory_uncheked(const fs::path& path_to_directory, const fs::path& path_to_answers, 
			const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent);
	};
}
