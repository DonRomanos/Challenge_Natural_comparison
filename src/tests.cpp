#include "reference.hpp"
#include "implement_here.hpp"
#include "gtest/gtest.h"

#include<vector>
#include<string>

// Experiment pass the functions directly as types and see what happens same signature!
// Check a little bit whats possible here!

// How do I instantiate the same test with different functions for reference and actual implementation?
// Possibility: Value Parametrized Tests -> Pass the test as function

/***************************************************************/
/* Actual tests */
TEST(AlphanumericalComparisonTests, Natural_ordering_is_fulfilled)
{
    std::vector<std::string> input = { "abc10c","abc1000ddd", "abc1c", "abc2c","abc001", "abc100", "abc01" };
    std::vector<std::string> expected = { "abc001", "abc01", "abc1c", "abc2c", "abc10c", "abc100", "abc1000ddd" };

    std::sort(input.begin(), input.end(), natural_compare);

    EXPECT_EQ(input, expected);
}

TEST(AlphanumericalComparisonTests, Comparison_with_multiple_number_sequences_works)
{
    std::vector<std::string> input = { "abc100_001","abc100_010", "abc100_2c"};
    std::vector<std::string> expected = { "abc100_001", "abc100_2c", "abc100_010" };

    std::sort(input.begin(), input.end(), natural_compare);

    EXPECT_EQ(input, expected);
}

TEST(AlphanumericalComparisonTests, More_prepending_zeros_should_come_first)
{
    std::vector<std::string> input = { "abc1", "abc0001", "abc01" };
    std::vector<std::string> expected = { "abc0001", "abc01", "abc1" };

    std::sort(input.begin(), input.end(), natural_compare);

    EXPECT_EQ(input, expected);
}

TEST(AlphanumericalComparisonTests, Comparison_is_case_sensitive)
{
    std::vector<std::string> input = { "abc1", "Abc0001", "ac01" };
    std::vector<std::string> expected = { "Abc0001", "abc1", "ac01" };

    std::sort(input.begin(), input.end(), natural_compare);

    EXPECT_EQ(input, expected);
}

TEST(AlphanumericalComparisonTests, When_one_is_prefix_of_the_other_longer_one_should_come_last)
{
    std::vector<std::string> input = { "abc1eeee", "abc1" };
    std::vector<std::string> expected = { "abc1", "abc1eeee" };

    std::sort(input.begin(), input.end(), natural_compare);

    EXPECT_EQ(input, expected);
}

TEST(AlphanumericalComparisonTests, Handling_empty_strings_should_not_throw)
{
    EXPECT_TRUE(natural_compare("", "") == 0);
}

// Had some Problems with the conan cmake_find_package generator, 
// it does not generate the correct targets therefore we dont have a gtest_main target
// so I write my own main.
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}