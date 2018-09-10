#include <iostream>

#include "gtest/gtest.h"

int main(int argc, char **argv) 
{
#if defined(_M_X64) || defined(__LP64__)
	std::cout << "x64" << std::endl;
#else 
	std::cout << "x86" << std::endl;
#endif

#if defined(_DEBUG) || !defined(NDEBUG)
	std::cout << "DEBUG" << std::endl;
#else	
	std::cout << "RELEASE" << std::endl;
#endif

	std::cout << "Running main() from gtest_main.cc" << std::endl;
	testing::InitGoogleTest(&argc, argv);

	auto result = RUN_ALL_TESTS();
	return result;
}
