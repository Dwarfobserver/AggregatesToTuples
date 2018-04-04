
# Aggregates to tuples

[![GCC Build Status](https://travis-ci.org/Dwarfobserver/AggregatesToTuples.svg?branch=master)](https://travis-ci.org/Dwarfobserver/AggregatesToTuples)

[![MSVC Build Status](https://ci.appveyor.com/api/projects/status/github/Dwarfobserver/AggregatesToTuples?svg=true)](https://ci.appveyor.com/project/Dwarfobserver/aggregatestotuples)

This is a single-header library in partial C++17 which enable to treat aggregate (or record) types as tuples.
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

att::as_tuple_t<person> refs  = att::as_tuple(alex); // std::tuple<std::string&, int&>
att::to_tuple_t<person> tuple = att::to_tuple(alex); // std::tuple<std::string, int>

size_t hash = att::hash(alex); // string hash combined with int hash

using namespace att::operators;

bool eq = alex == alex2;       // false
bool lt = alex < alex2;        // true

std::ostringstream stream;
stream << alex;                // stream.str() == "Alex24"

```

Tests can be built and launched with :

```bash

mkdir build
cd build
cmake ..
cmake --build .
ctest -V

```

'single_include/aggregates_to_tuples.hpp' and 'include/arity_functions.inl' are created by the programs
contained in 'generators'.

The python file 'full_build.py' can be called from your build directory (which must be in the root directory
of the project) to build and execute generators, then build and launch tests.

Project limitations :

 - The aggregate max size is limited (it can be increased with the arity_functions generator)
 - It does not support aggregates with native arrays (eg. T[N], use std::array<T, N> instead)

Note : std::is_aggregate<T> is not used because it is not implemented in MSVC (and not Clang from what I saw), but it would
avoid some types detection caveats and greatly reduce compile time.
