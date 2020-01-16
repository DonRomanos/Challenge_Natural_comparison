#include "reference.hpp"
#include "implement_here.hpp"
#include "gtest/gtest.h"

#include<vector>
#include<string>

// Experiment pass the functions directly as types and see what happens same signature!
// Check a little bit whats possible here!

// How do I instantiate the same test with different functions for reference and actual implementation?
// Possibility: Value Parametrized Tests --> Pass the test as function

/***************************************************************/
/* Actual tests */
TEST(AlphanumericalComparisonTests, Prepending_zeros_should_come_after_no_zeroes)
{
    std::vector<std::string> input = { "abc1", "abc0001", "abc01" };
    std::vector<std::string> expected = { "abc1", "abc01", "abc0001" };

    std::sort(input.begin(), input.end(), isSmaller);

    EXPECT_EQ(input, expected);
}

// Had some Problems with the conan cmake_find_package generator, 
// it does not generate the correct targets therefore we dont have a gtest_main target
// so I write my own main.
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}