#pragma once

#include <string_view>
#include <stdexcept>

/* Challenge: 
Provide the natural_compare function that can be passed to** std::sort** which will sort the elements so that all of the following requirements are met.

* natural order is fulfilled with any numbers, e.g.  "abc2c" comes before "abc10c"
* if two numbers are equal but have a different number of prepending zeros, the one with more prepending zeros should come first, e.g. "0010_abc" before "010_abc"
* capital letters should come first, e.g. "Abc" before "abc"
* you do not need to consider negative numbers e.g. - is not treated as part of a number
* floating point numbers are also not considered e.g. "abc100.2" and "abc100.01" don't have to work
* we only care about ascii characters

* *This should be fulfilled when all unit tests are green!**

* There is a performance comparison available with the Benchmark.exe where you can test your implementation against mine ;) let me know about the results.
*/

bool natural_compare(std::string_view left, std::string_view right)
{
	throw std::runtime_error("Heeeeeelp");
}

// Signature of the above function this is used in the Benchmark and the Tests, if you change it, make sure it still compiles :)
using ChallengeSignature = bool(*)(std::string_view, std::string_view);