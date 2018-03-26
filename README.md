
# Aggregates to tuples

[![Build Status](https://travis-ci.org/Dwarfobserver/AggregatesToTuples.svg?branch=master)](https://travis-ci.org/Dwarfobserver/AggregatesToTuples)

This is a personal project in C++17 which enable to treat aggregate (or record) types as tuples.
It has been inspired by this nice article : https://playfulprogramming.blogspot.ca/2016/12/serializing-structs-with-c17-structured.html

Using tuples instead of aggregates can allow many functional programming algorithms, or automatic serialization.

Little exemple of use (in tests/printer.cpp) :

```cpp

struct person {
    std::string name, int age;
};

std::ostringstream stream;

person p{ "Alex", 24 };
stream << att::as_tuple(p);

// stream.str() == "{ Alex 24 }"

```

Tests can be built and launched with :

```bash

mkdir build
cd build
cmake ..
cmake --build .
ctest

```

This project in under construction and lacks features and tests.
In particular :

 - The aggregate max size is limited (it can be increased by copy-paste code)
 - It does not give any code to manipulate tuples
 - It cannot change structures to tuples recursively (eg. struct couple { person p1, person, p2 } giving tuple<tuple<...>>)
 - It does not support aggregates with native arrays (eg. T[N], use std::array<T, N> instead)
 - It is not precisely tested and serves more as a proof of concept

Code to manipulate tuples is not in the scope of this project, but there is basic tuple manipulations in the exemples.

Note : std::is_aggregate<T> is not used because it is not implemented in MSVC (and not Clang from what I saw), but it would
avoid some types detection caveats and greatly reduce compile time.
