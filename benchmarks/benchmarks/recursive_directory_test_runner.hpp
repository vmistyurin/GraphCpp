#pragma once

#include <chrono>

#include <boost/filesystem.hpp>

namespace graphcpp_bench
{
	namespace fs = boost::filesystem;

	class RecursiveDirectoryTestRunner final 
	{
    private:
        const fs::path _path_to_tests;
        const fs::path _result_path;
        std::ostream& _logger;
        std::list<std::string> _runned_tests;
        
	public:
        explicit RecursiveDirectoryTestRunner(fs::path path_to_tests, fs::path result_path, std::ostream& logger);
        
		void run_tests(std::function<std::string(std::ifstream&&)> test_function, std::string_view test_name);
        void print_check_result();

	private:
        std::list<fs::path> check_results(const fs::path& first_answers, const fs::path& second_answers);

        std::chrono::milliseconds run_single_test(const fs::path& path_to_test, const fs::path& result_path,
            const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent = 0);
        
		void run_tests_in_directory_uncheked(const fs::path& path_to_directory, const fs::path& result_path,
			const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent);
	};
}
