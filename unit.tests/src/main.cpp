#include <stdio.h>
#include "gtest/gtest.h"

int main(int argc, char **argv) 
{
#ifdef DEBUG
	printf("DEBUG");
#else	
	printf("RELEASE");
#endif // DEBUG

	printf("Running main() from gtest_main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
