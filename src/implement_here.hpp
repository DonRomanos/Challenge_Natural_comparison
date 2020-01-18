#include <iostream>
#include <charconv>
#include <string_view>
#include <cctype>
#include <algorithm>

// To do: 3-way comparison with strong ordering
bool isSmaller(std::string_view left, std::string_view right)
{
	// completely empty strings compare     -> done
	// different lenghts but same till end  -> done
	// ends in same digits                  -> done
	// prepend 00000s e.g. abc0001efg... abc1efg... -> done
	// handle really long numbers --> find out how many chars fit into your type instead of end use that

	// Bonus: What if you want a sorting to consider the number of zeros, e.g. least zeros come first.
	// Bonus: Considering negative values --> currently we do not recognize - as minus
	const auto minimum_size = std::min(left.size(), right.size());
	const auto digits = "0123456789";
	for (int left_index = 0, right_index = 0; left_index < minimum_size && right_index < minimum_size;)
	{
		while (left[left_index] == right[right_index] && left_index < minimum_size && right_index < minimum_size)
		{
			++left_index;
			++right_index;
		}
		if (std::isdigit(left[left_index]) && std::isdigit(right[right_index]))
		{
			auto sequence_end_left = left_index + 1;
			for (; sequence_end_left < left.size() && std::isdigit(left[sequence_end_left]); ++sequence_end_left);
			auto sequence_end_right = right_index + 1;
			for (; sequence_end_right < right.size() && std::isdigit(right[sequence_end_right]); ++sequence_end_right);

			unsigned int left_value, right_value;
			// No error handling ... as there should not be any conversion error possible since we only convert characters
			std::from_chars(left.data() + left_index, left.data() + sequence_end_left, left_value);
			std::from_chars(right.data() + right_index, right.data() + sequence_end_left, right_value);
			if (left_value == right_value)
			{
				left_index = sequence_end_left;
				right_index = sequence_end_right;
				continue;
			}
			return left_value < right_value;
		}
		// Handle only one of them is a digit.
		return left[left_index] < right[right_index];
	}
	return left.size() < right.size();

	/*for (auto left_char = left.begin(), right_char = right.begin(); left_char != left.end() && right_char != right.end(); ++left_char, ++right_char)
	{
		if (*left_char == *right_char)
		{
			continue;
		}
		else if (std::isdigit(*left_char) && std::isdigit(*right_char))
		{
			constexpr unsigned int maximum_number_of_chars_in_int = std::numeric_limits<unsigned int>::max() / 9;
			auto sequence_end_left = left.size() < (left_char - left.begin()) + maximum_number_of_chars_in_int ? left.end() : left_char + maximum_number_of_chars_in_int;
			auto sequence_end_right = right.size() < (right_char - right.begin()) + maximum_number_of_chars_in_int ? right.end() : right_char + maximum_number_of_chars_in_int;
			auto end_of_digit_sequence_left = std::find_if(left_char, sequence_end_left, [](const unsigned char in) {return !std::isdigit(in); });
			auto end_of_digit_sequence_right = std::find_if(right_char, sequence_end_right, [](const unsigned char in) {return !std::isdigit(in); });

			unsigned int left_value, right_value;
			std::from_chars(left_char, end_of_digit_sequence_left, left_value);
			std::from_chars(right_char, end_of_digit_sequence_right, right_value);
			
			if (left_value == right_value)
			{
				left_char = end_of_digit_sequence_left;
				right_char = end_of_digit_sequence_right;
				continue;
			}
			else
			{
				return left_value < right_value;
			}
		} 
		return *left_char < *right_char;
	}
	return left.size() < right.size();*/
}


// Learnings:
// no need for const in string_view ? -> confirm
// You can assign values in if and have the condition
// One for loop for multiple iterators is possible
// from_chars uses an output variable while returning a pair to signal error condition, interesting design
// You cannot add to an iterator behind the end of the container, e.g. for checking a condition
// Never dereference iterators if you dont have to, especially end iterators you moron!
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
//                       not a <= b, b <= a means they are incomparable