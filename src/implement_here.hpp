#include <iostream>
#include <charconv>
#include <string_view>
#include <cctype>
#include <compare>
#include <algorithm>

// solution two for strings with std::missmatch and iterators
// todo here:

int natural_3way_compare(std::string_view left, std::string_view right)
{
	auto left_index = 0, right_index = 0;
	for (; left_index < left.size() && right_index < right.size() ; ++left_index, ++right_index)
	{
		if (std::isdigit(left[left_index]) && std::isdigit(right[right_index]))
		{
			auto sequence_end_left = left_index + 1;
			for (; sequence_end_left < left.size() && std::isdigit(left[sequence_end_left]); ++sequence_end_left);
			auto sequence_end_right = right_index + 1;
			for (; sequence_end_right < right.size() && std::isdigit(right[sequence_end_right]); ++sequence_end_right);

			unsigned int left_value, right_value;
			// No error handling ... as there should not be any conversion error possible since we only convert digits
			std::from_chars(left.data() + left_index, left.data() + sequence_end_left, left_value);
			std::from_chars(right.data() + right_index, right.data() + sequence_end_right, right_value);
			if (left_value == right_value)
			{
				// When prepending zeros are in we compare the size more prepending zeroes must come first.
				if (sequence_end_left - left_index > sequence_end_right - right_index)
				{
					return -1;
				}
				else if (sequence_end_left - left_index < sequence_end_right - right_index)
				{
					return 1;
				}
				left_index = sequence_end_left-1;
				right_index = sequence_end_right-1;
				continue;
			}
			else if ( left_value < right_value)
			{
				return -1;
			}
			return 1;
		}
		else if(left[left_index] == right[right_index])
		{
			continue;
		}
		return right[right_index] - left[left_index];
	}
	if (left.size() < right.size())
	{
		return -1;
	}
	else if (left.size() > right.size())
	{
		return 1;
	}
	return 0;
}


bool natural_compare(std::string_view left, std::string_view right)
{
	return natural_3way_compare(left, right) < 0;
}


// Learnings:
// no need for const in string_view does not make sens
// string_views are not guaranteed null terminated
// You can assign values in if and have the condition
// One for loop for multiple iterators is possible
// from_chars uses an output variable while returning a pair to signal error condition, interesting design
// You cannot add to an iterator behind the end of the container, e.g. for checking a condition
// Never dereference iterators if you dont have to, especially end iterators you moron!
// 

/* Iterators tend to draw you sometimes to not the best solutions, compare my approach first the one now vs the one before 

    const auto minimum_size = std::min(left.size(), right.size());
	for (int i = 0; i < minimum_size && (left[i] == right[i]); ++i)
	{ ... }

	for (auto left_char = left.begin(), right_char = right.begin(); left_char != left.end() && right_char != right.end(); ++left_char, ++right_char)
	{ ... }

	// TODO check the assembly for both loops with optimizations
*/

// Strict weak ordering: a < b, => ! b < a, if not a < b and not b < a, then == equivalent
// Weak ordering:        a <= b && b <= a means they are either equivalent, but if 
//                       not a <= b, and not b <= a means they are incomparable