# Write a C++ natural sorting algorithm

A small problem I once encountered and deemed interesting.

## Task

We want to sort a collection of strings which contain letters and numbers in a natural way, meaning like a human would. Example sequence after sorting:

* abcd0001
* abcd01
* abcd1
* abcd10
* abcd1000

This is in contrast to the standard lexicographical comparison the regular strings use, but often needed for example for UIs to show data in a correct and expected order.

I added a few specialities, e.g. we differentiate prepending zeros in numbers, and we consider cases of letters.

### Requirements

Provide a function that can be passed to **std::sort** which will sort the elements so that all of the following requirements are met.

* natural order is fulfilled with any numbers, e.g.  "abc2c" comes before "abc10c"
* if two numbers are equal but have a different number of prepending zeros, the one with more prepending zeros should come first, e.g. "0010_abc" before "010_abc"
* capital letters should come first, e.g. "Abc" before "abc"
* you do not need to consider negative numbers e.g. - is not treated as part of a number
* floating point numbers are also not considered e.g. "abc100.2" and "abc100.01" don't have to work

**This should be fulfilled when all unit tests are green!**

## Goal

Write a conciouscious implementation of a common algorithm, consider readability and performance.

**Note:**
There is a benchmark, where you can compare your implementation against mine in terms of performance. I am really curious about any results you get, let me know.

## How to use

Requirements:

* CMake
* Conan
* Python (for Conan)
* C++20 capable compiler

Setting up a Conan profile for your environment

```shell
conan profile new WhateverCompilerSettingsYouWant --detect
```

For more Infos see: [<https://docs.conan.io/en/latest/reference/profiles.html]>

Installing the Libraries using Conan

```shell
mkdir build && cd build
conan install .. --build missing -p WhateverCompilerSettingsYouWant
conan build ..
```

Now you should see the library successfully compiling and running the tests.

**Note:**
If you don't have the dependencies or dont want to build with them for some reason you can disable them with these CMake Options, simply set them to 'OFF'.

```cmake
BUILD_REFERENCE
BUILD_TESTS
BUILD_BENCHMARK
```

### Alternative without Conan

Requirements:

* CMake

You can build the library without Conan if you manually install the gtest and google benchmark libraries.

Just tell Cmake where to find them by setting following CMake Variables

```cmake
gtest_DIR
benchmark_ROOT_DIR
```

You can do so via command line

```shell
cmake -Dgtest_DIR=usr/local/...
```

or via the gui by adding a path entry with the name.

## Learnings and Explanations

If you are curious how my implementation went and what I learned during developement take a peek.

<details><summary>Spoiler Alert</summary>
<p>

I changed my approach during developement quite a bit, you can check the first git commits, compared to my final code and get a grasp of the developement. In the beginning I tried to have the complete algorithm within one function, but it became quite complex and unreadable so I ended up splitting it up.

In the end this seems to be the better way to me, as its more concise and can be more easily adapted to for example a change in requirements (since digits and regular characters are handled in different functions for example ignoring spaces can be added quite easily).

It was quite a suprise how complex such a seemingly simple algorithm would become when all the requirements were considered.

Separating the algorithm in terms of different requirement, e.g. for numbers and characters worked quite well to reduce the complexity and focus on partial problems then the implementation went much smoother. **-->Recommended**

### Short remarks

* **string_view** does not work well with iterators, I had to use indices instead
* **from_chars** is not constexpr so I could not make my implementation constexpr

</p>
</details>

## For the Future

* An implementation with strings and iterators would be cool for performance comparison. For that the current approach can probably be templated and reused.
* This would be an interesting candidate for performance analysis and improvements maybe I can write a second version which focusses solely on performance
* Handling for floating point numbers can be added
* Handling of negative numbers can be added

## Please give me some Feedback if this helped or you have any suggestions or remarks
