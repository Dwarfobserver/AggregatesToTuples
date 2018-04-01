
# Aggregates to tuples

[![Build Status](https://travis-ci.org/Dwarfobserver/AggregatesToTuples.svg?branch=master)](https://travis-ci.org/Dwarfobserver/AggregatesToTuples)

This is a personal project in partial C++17 which enable to treat aggregate (or record) types as tuples.
It works for MSVC, Clang and GCC.
It has been inspired by this nice article : https://playfulprogramming.blogspot.ca/2016/12/serializing-structs-with-c17-structured.html

Using tuples instead of aggregates can allow many functional programming algorithms and automatic
properties, such as equality comparaison, serialization or hash.

Little exemple of use :

```cpp

struct person {
    std::string name;
    int age;
};

person alex  { "Alex", 24 };
person alex2 { "Alex", 25 };

att::as_tuple_t<person> refs = att::as_tuple(alex); // std::tuple<std::string&, int&>
att::to_tuple_t<person> tuple = att::to_tuple(alex); // std::tuple<std::string, int>

using namespace att::operators;

bool lt = alex < alex2; // true

```

Tests can be built and launched with :

```bash

mkdir build
cd build
cmake ..
cmake --build .
ctest -V

```

The 'generators' folder has two programs :

 - arity_functions which creates the 'arity_functions.inl' file.
 - single_include which glues together the files in 'include' into a unique header in 'single_include'.

If you want to use them, they must be built with the cmake on your machine. To do that, call cmake with
-DMAKE_GENERATORS=1 : it will build the generators instead of the tests.

This project in under construction and lacks features and tests.
In particular :

 - The aggregate max size is limited (it can be increased with the arity_functions generator)
 - It does not support aggregates with native arrays (eg. T[N], use std::array<T, N> instead)
 - It is not precisely tested and serves more as a proof of concept

Note : std::is_aggregate<T> is not used because it is not implemented in MSVC (and not Clang from what I saw), but it would
avoid some types detection caveats and greatly reduce compile time.
