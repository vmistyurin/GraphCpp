#include "functional.tests/recursive_directory_test_runner.h"
#include <type_traits>
#include <iostream>
#include <fstream>

using namespace graphcpp_bench;

namespace {
	std::string get_indent_string(unsigned int indent)
	{
		return std::string(indent, '\t');
	}
}

std::chrono::milliseconds RecursiveDirectoryTestRunner::run_single_test(const fs::path& path_to_test, const fs::path& path_to_answer,
	const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent)
{
	std::ifstream input(path_to_test.string());

	std::chrono::system_clock clock;
	auto start = clock.now();

	auto result = test_function(std::move(input));

	auto finish = clock.now();

	auto duration = finish - start;
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	std::cout << get_indent_string(indent) << "Test " << path_to_test.filename() << " ended, time = "
		<< time.count() << "ms " << std::endl;

	std::ofstream output(path_to_answer.string());
	output << result;
	output.close();

	return time;
}

void RecursiveDirectoryTestRunner::run_tests_in_directory(const fs::path& path_to_directory, const fs::path& path_to_answers, 
	const std::function<std::string(std::ifstream&&)>& test_function)
{
	if (fs::exists(path_to_answers))
	{
		fs::remove_all(fs::canonical(path_to_answers));
	}
	run_tests_in_directory_uncheked(path_to_directory, path_to_answers, test_function, 0);
}

void RecursiveDirectoryTestRunner::run_tests_in_directory_uncheked(const fs::path& path_to_directory, const fs::path& path_to_answers, 
	const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent)
{
	std::cout << get_indent_string(indent) << "Tests for directory " << path_to_directory.filename() << " has started" << std::endl;
	fs::create_directory(path_to_answers);

	unsigned int count = 0;
	auto time = std::chrono::milliseconds::zero();

	for (const auto& file : fs::directory_iterator(path_to_directory))
	{
		auto filename = file.path().filename();

		if (fs::is_directory(file))
		{
			run_tests_in_directory_uncheked(path_to_directory / filename, path_to_answers / filename, test_function, indent + 1);
		}
		else
		{
			time += run_single_test(file, path_to_answers / filename, test_function, indent + 1);
			count++;
		}
	}

	std::cout << get_indent_string(indent) << "Tests for directory " << path_to_directory.filename() << " has ended ";
	if (count > 0)
	{
		std::cout << "average time = " << time.count() / count << "ms" << std::endl;
	}
}