#pragma once

#include <charconv>
#include <string_view>
#include <cctype>

namespace detail
{
	constexpr inline int compare_character(const char lhs, const char rhs)
	{
		if (lhs == rhs)	return 0;
		else if (lhs < rhs)	return -1;
		else return 1;
	}

	constexpr inline int compare_number(unsigned int lhs, unsigned int rhs)
	{
		// Could be written as return abs(lhs-rhs) but i find this clearer (also no casts neccessary because of the unsigned)
		if (lhs == rhs) return 0;
		else if (lhs < rhs) return -1;
		else return 1;
	}

	inline int to_number(std::string_view digits)
	{
		unsigned int value;
		std::from_chars(digits.data(), digits.data() + digits.size(), value);
		// no error handling as input of digits should never produce an error.
		return value;
	}

	inline int compare_digit_sequence(std::string_view lhs, std::string_view rhs)
	{
		auto lhs_value = to_number(lhs);
		auto rhs_value = to_number(rhs);
		if (lhs_value < rhs_value) return -1;
		else if (lhs_value > rhs_value) return +1;

		// We want sort according to prepending zeros if values are equal
		if (lhs.size() == rhs.size()) return 0;
		else if (lhs.size() > rhs.size()) return -1;
		else return 1;
	}

	constexpr inline int compare_size(std::string_view lhs, std::string_view rhs)
	{
		if (lhs.size() == rhs.size()) return 0;
		else if (lhs.size() < rhs.size()) return -1;
		else return 1;
	}

	constexpr inline int get_length_of_digit_sequence(std::string_view digit_sequence)
	{
		auto counter = 0;
		while (counter < digit_sequence.size() && std::isdigit(digit_sequence[counter]))
		{
			++counter;
		}
		return counter;
	}
};

int natural_3way_compare(std::string_view lhs, std::string_view rhs)
{
	using namespace detail;
	for (auto lhs_index = 0, rhs_index = 0; lhs_index < lhs.size() && rhs_index < rhs.size(); ++lhs_index, ++rhs_index)
	{
		if (std::isdigit(lhs[lhs_index]) && std::isdigit(rhs[rhs_index]))
		{
			auto lhs_number_length = get_length_of_digit_sequence(lhs.substr(lhs_index));
			auto rhs_number_length = get_length_of_digit_sequence(rhs.substr(rhs_index));
			if (auto result = compare_digit_sequence(lhs.substr(lhs_index, lhs_number_length), rhs.substr(rhs_index, rhs_number_length)); result != 0)
			{
				return result;
			}
			// update "iterators"
			lhs_index += lhs_number_length - 1;
			rhs_index += rhs_number_length - 1;
		}
		else if(auto result = compare_character(lhs[lhs_index], rhs[rhs_index]); result != 0)
		{
			return result;
		}
	}
	return compare_size(lhs, rhs);
}


bool natural_compare(std::string_view left, std::string_view right)
{
	return natural_3way_compare(left, right) < 0;
}

// Learnings:
// no need for const in string_view does not make sense since nothing can modify it anyway
// string_views are not guaranteed null terminated
// from_chars uses an output variable while returning a pair to signal error condition, interesting design
// You cannot add to an iterator behind the end of the container, e.g. for checking a condition even if you never dereference it
// Never dereference iterators if you dont have to, especially end iterators
// from_chars is not constexpr

// Strict weak ordering: a < b, => ! b < a, if not a < b and not b < a, then == equivalent
// Weak ordering:        a <= b && b <= a means they are either equivalent, but if 
//                       not a <= b, and not b <= a means they are incomparable

// template Non-types can be a
// lvalue reference, nullptr, pointer, enumerator, integral
// meaning you can define templates like this: template<int(*functionp)(int)> void doSomething() and instantiate it like this template void doSomething<function>();
// Compile time function pointers :p