#include "benchmarks/recursive_directory_test_runner.hpp"

#include <string_view>

using namespace graphcpp::bench;

namespace 
{
	std::string get_indent_string(unsigned int indent)
	{
		return std::string(indent, '\t');
	}
    
    bool two_files_equal(const fs::path& first_file, const fs::path& second_file)
    {
        std::ifstream first_stream(first_file.string());
        std::ifstream second_stream(second_file.string());
        
        const auto end_iterator = std::istream_iterator<char>();
        
        return std::equal(std::istream_iterator<char>(first_stream), end_iterator,
                          std::istream_iterator<char>(second_stream), end_iterator);
    }
}

RecursiveDirectoryTestRunner::RecursiveDirectoryTestRunner(fs::path path_to_tests, fs::path result_path, std::ostream& logger) :
    _path_to_tests(std::move(path_to_tests)), _result_path(std::move(result_path)), _logger(logger)
{
    if (fs::exists(_result_path))
    {
        fs::remove_all(fs::canonical(_result_path));
    }
    fs::create_directory(_result_path);
}

void RecursiveDirectoryTestRunner::run_tests(std::function<std::string(std::ifstream&&)> test_function, std::string_view test_name)
{
    _logger << "Test " << test_name << " has started" << std::endl;
    
	assert(std::find(_runned_tests.cbegin(), _runned_tests.cend(), test_name) == _runned_tests.cend());
	_runned_tests.emplace_back(test_name);
    
    run_tests_in_directory_uncheked(_path_to_tests, _result_path / _runned_tests.back(), test_function, 0);
    
    _logger << std::endl;
}

void RecursiveDirectoryTestRunner::run_tests_in_directory_uncheked(const fs::path& path_to_directory, const fs::path& result_path,
    const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent)
{
    _logger << get_indent_string(indent) << "Tests for directory " << path_to_directory.filename() << " have started" << std::endl;
    fs::create_directory(result_path);
    
    unsigned int count = 0;
    auto time = std::chrono::milliseconds::zero();
    
    for (const auto& file : fs::directory_iterator(path_to_directory))
    {
        auto filename = file.path().filename();
        
        if (fs::is_directory(file))
        {
            run_tests_in_directory_uncheked(path_to_directory / filename, result_path / filename, test_function, indent + 1);
        }
        else
        {
            if (const auto test_name = file.path().filename(); test_name.string()[0] != '.')
            {
                time += run_single_test(file, result_path / filename, test_function, indent + 1);
                count++;
            }
        }
    }
    
    _logger << get_indent_string(indent) << "Tests for directory " << path_to_directory.filename() << " have ended";
    if (count > 0)
    {
        _logger << ", average time = " << time.count() / count << "ms";
    }
    _logger << std::endl;
}

std::chrono::milliseconds RecursiveDirectoryTestRunner::run_single_test(const fs::path& path_to_test, const fs::path& result_path,
	const std::function<std::string(std::ifstream&&)>& test_function, unsigned int indent)
{
	std::ifstream input(path_to_test.string());

    _logger << get_indent_string(indent) << "Test " << path_to_test.filename() << " has started ... ";
	std::chrono::system_clock clock;
	auto start = clock.now();

	auto result = test_function(std::move(input));

	auto finish = clock.now();

	auto duration = finish - start;
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	_logger << "has ended, time = " << time.count() << "ms " << std::endl;

	std::ofstream output(result_path.string());
	output << result;
	output.close();

	return time;
}

std::list<fs::path> RecursiveDirectoryTestRunner::check_results(const fs::path& first_answers, const fs::path& second_answers) const
{
	std::list<fs::path> result;

	for (const auto& file : fs::directory_iterator(first_answers))
	{
		const auto filename = file.path().filename();

		if (fs::is_directory(file))
		{
			auto directory_result = check_results(first_answers / filename, second_answers / filename);
			result.merge(std::move(directory_result));
		}
		else
		{
            if (!two_files_equal(first_answers / filename, second_answers / filename))
            {
                result.push_back(first_answers / filename);
            }
		}
	}
	
	return result;
}

void RecursiveDirectoryTestRunner::print_check_result() const
{
    if (_runned_tests.size() < 2)
    {
        throw std::logic_error("Too few tests to compare");
    }
    
    const auto standart_test_name = _runned_tests.front();
    const auto standart_path = _result_path / standart_test_name;
    
    for (auto comparable_test = std::next(_runned_tests.cbegin()); comparable_test != _runned_tests.cend(); comparable_test++)
    {
        const auto comparable_path = _result_path / *comparable_test;
        
        if (const auto differences = check_results(standart_path, comparable_path); differences.empty())
        {
            _logger << "No differences";
        }
        else
        {
            _logger << "There are " << differences.size() << " differences" << std::endl;
            for (const auto& path : differences)
            {
                _logger << path.string() << std::endl;
            }
        }
        _logger << " between " << standart_test_name << " and " << *comparable_test << std::endl;
    }
}
