#include <iostream>

#include "gtest/gtest.h"

int main(int argc, char **argv) 
{
#ifdef _M_X64
	std::cout << "x64" << std::endl;
#else 
	std::cout << "x86" << std::endl;
#endif // _M_X64

#ifdef _DEBUG
	std::cout << "DEBUG" << std::endl;
#else	
	std::cout << "RELEASE" << std::endl;
#endif // _DEBUG

	std::cout << "Running main() from gtest_main.cc" << std::endl;
	testing::InitGoogleTest(&argc, argv);

	auto result = RUN_ALL_TESTS();
	return result;
}
