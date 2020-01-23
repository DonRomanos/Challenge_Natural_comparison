#include "reference.hpp"
#include "challenge.hpp"
#include "gtest/gtest.h"

#include<vector>
#include<string>

// I could not make this work with type-parametrized tests, because I would need to declare a typedef like this:
// using TypesToTest = ::testing::Types<reference::GetParam(), GetParam()>;
// which does not compile since the function names are not actual types. ( if somebody knows how to do it, I would be interested)

class NaturalComparisonTest : public testing::TestWithParam<ChallengeSignature>
{};

/***************************************************************/
/* Actual tests */
TEST_P(NaturalComparisonTest, Natural_ordering_is_fulfilled)
{
    std::vector<std::string> input = { "abc10c","abc1000ddd", "abc1c", "abc2c","abc001", "abc100", "abc01" };
    std::vector<std::string> expected = { "abc001", "abc01", "abc1c", "abc2c", "abc10c", "abc100", "abc1000ddd" };

    std::sort(input.begin(), input.end(), GetParam());

    EXPECT_EQ(input, expected);
}

TEST_P(NaturalComparisonTest, Comparison_with_multiple_number_sequences_works)
{
    std::vector<std::string> input = { "abc100_001","abc100_010", "abc100_2c"};
    std::vector<std::string> expected = { "abc100_001", "abc100_2c", "abc100_010" };

    std::sort(input.begin(), input.end(), GetParam());

    EXPECT_EQ(input, expected);
}

TEST_P(NaturalComparisonTest, More_prepending_zeros_should_come_first)
{
    std::vector<std::string> input = { "abc1", "abc0001", "abc01" };
    std::vector<std::string> expected = { "abc0001", "abc01", "abc1" };

    std::sort(input.begin(), input.end(), GetParam());

    EXPECT_EQ(input, expected);
}

TEST_P(NaturalComparisonTest, Comparison_is_case_sensitive)
{
    std::vector<std::string> input = { "abc1", "Abc0001", "ac01" };
    std::vector<std::string> expected = { "Abc0001", "abc1", "ac01" };

    std::sort(input.begin(), input.end(), GetParam());

    EXPECT_EQ(input, expected);
}

TEST_P(NaturalComparisonTest, When_one_is_prefix_of_the_other_longer_one_should_come_last)
{
    std::vector<std::string> input = { "abc1eeee", "abc1" };
    std::vector<std::string> expected = { "abc1", "abc1eeee" };

    std::sort(input.begin(), input.end(), GetParam());

    EXPECT_EQ(input, expected);
}

TEST_P(NaturalComparisonTest, Handling_empty_strings_should_not_throw)
{
    EXPECT_FALSE(GetParam()("", ""));
}

TEST_P(NaturalComparisonTest, Comparing_single_digit_strings_should_not_throw)
{
    EXPECT_TRUE(GetParam()("1", "2"));
}

INSTANTIATE_TEST_CASE_P(ChallengeTests, NaturalComparisonTest, testing::Values(natural_compare));
INSTANTIATE_TEST_CASE_P(ReferenceTests, NaturalComparisonTest, testing::Values(reference::natural_compare));

// Had some Problems with the conan cmake_find_package generator, 
// it does not generate the correct targets therefore we dont have a gtest_main target
// so I write my own main.
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}