#include <iostream>

#include "core/utils/system_info.hpp"

#include "gtest/gtest.h"

int main(int argc, char **argv) 
{
	std::cout << graphcpp::system_info() << std::endl;
	
	std::cout << "Running main() from main.cpp" << std::endl;
	testing::InitGoogleTest(&argc, argv);

	auto result = RUN_ALL_TESTS();
	return result;
}
