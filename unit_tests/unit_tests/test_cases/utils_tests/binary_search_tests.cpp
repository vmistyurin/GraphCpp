#include "gtest/gtest.h"

#include "core/utils/numeric.hpp"

#ifdef USE_UTILS_TESTS

namespace graphcpp::testing
{
    TEST(UtilsTests, BinarySearchSuccessTest)
    {
        std::vector<msize> vector = { 0, 1, 4, 6, 10 };
        
        EXPECT_EQ(binary_search(vector, 4), std::find(vector.cbegin(), vector.cend(), 4));
    }
    
    TEST(UtilsTests, BinarySearchFailTest)
    {
        std::vector<msize> vector = { 0, 1, 4, 6, 10 };
        
        EXPECT_EQ(binary_search(vector, 5), std::find(vector.cbegin(), vector.cend(), 5));
    }
    
    TEST(UtilsTests, BinarySearchFirstTest)
    {
        std::vector<msize> vector = { 0, 1, 4, 6, 10 };
        
        EXPECT_EQ(binary_search(vector, 0), std::find(vector.cbegin(), vector.cend(), 0));
    }
}

#endif

