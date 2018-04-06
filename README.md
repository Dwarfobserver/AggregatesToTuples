
# Aggregates to tuples

[![GCC Build Status](https://travis-ci.org/Dwarfobserver/AggregatesToTuples.svg?branch=master)](https://travis-ci.org/Dwarfobserver/AggregatesToTuples)

[![MSVC Build Status](https://ci.appveyor.com/api/projects/status/github/Dwarfobserver/AggregatesToTuples?svg=true)](https://ci.appveyor.com/project/Dwarfobserver/aggregatestotuples)

This is a single-header library in partial C++17 which enable to treat aggregate (or record) types as tuples.
It works for MSVC, Clang and GCC.
It has been inspired by this nice article : https://playfulprogramming.blogspot.ca/2016/12/serializing-structs-with-c17-structured.html

Using tuples instead of aggregates can allow many functional programming algorithms and automatic
properties, such as equality comparaison, serialization or hash.

Overview of some features :

```cpp

struct info {
    int age;
    int size;
};
struct person {
    std::string name;
    info infos;
};

auto alex = person { "Alex", { 24, 182 } };

size_t hash = att::hash(alex); // combinaison of string hash and two int hash

using namespace att::operators;

std::ostringstream stream;
stream << alex;                // stream.str() == "{ Alex , { 24 , 182 } }"

auto alex2 = alex;
alex2.infos.size += 1;

bool eq = alex == alex2;       // false
bool lt = alex < alex2;        // true

att::as_tuple_t<person> refs  = att::as_tuple(alex); // std::tuple<std::string&, info&>
att::to_tuple_t<person> tuple = att::to_tuple(alex); // std::tuple<std::string, info>

auto alex3 = att::from_tuple(refs).make<person>();

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
