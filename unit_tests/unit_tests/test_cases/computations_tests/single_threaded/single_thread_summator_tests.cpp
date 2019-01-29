#include "gtest/gtest.h"

#include "core/computations/single_threaded/single_thread_summator.hpp"

using namespace graphcpp;

class SingleThreadSummatorTests : public ::testing::Test
{
protected:
    SingleThreadSummatorTests() :
        summator(std::make_unique<SingleThreadSummator<double>>(double(initial_value)))
    {
    }
    
    static inline double initial_value = 1;
    std::unique_ptr<SingleThreadSummator<double>> summator;
};

TEST_F(SingleThreadSummatorTests, AddTest)
{
    const auto added_probability = 0.5;
    auto added_value = 5.0;
    
    this->summator->add(added_value, added_probability);
    
    EXPECT_EQ(this->summator->current_sum(), 2.5 + initial_value);
    EXPECT_EQ(this->summator->current_probability(), added_probability);
}

TEST_F(SingleThreadSummatorTests, DoubleAddTests)
{
    auto first_added = std::pair(5.0, 0.5);
    auto second_added = std::pair(10.0, 0.3);
    
    this->summator->add(first_added.first, first_added.second);
    this->summator->add(second_added.first, second_added.second);

    EXPECT_EQ(this->summator->current_sum(), 5.5 + initial_value);
    EXPECT_EQ(this->summator->current_probability(), first_added.second + second_added.second);
}
