#include "gtest/gtest.h"

#include "core/utils/numeric.hpp"

#include "unit_tests/utils/comparators.hpp"

namespace graphcpp::testing
{
    #ifdef USE_UTILS_TESTS
        TEST(UtilsTests, AdditionTest)
        {
            std::vector<msize> numbers = { 3, 2, 5 };
            std::vector<msize> expected = { 0, 1, 4, 6 };
            
            EXPECT_TRUE(compare_without_order(find_addition(numbers, 7), expected));
        }
    #endif // USE_UTILS_TESTS
}
