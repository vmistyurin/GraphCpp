#include "gtest/gtest.h"

#include "core/utils/numeric.hpp"

using namespace graphcpp;

#ifdef USE_UTILS_TESTS
TEST(UtilsTests, ReduceVertexesNumberTest)
{
    std::vector<msize> vertexes = { 3, 6, 1 };
    std::vector<msize> deleted_vertexes = { 5, 0 };
    
    EXPECT_EQ(reduce_vertexes_numbers(vertexes, deleted_vertexes), std::vector<msize>({ 2, 4, 0 }));
}
#endif // USE_UTILS_TESTS
