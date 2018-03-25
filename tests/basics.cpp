
#include "catch.hpp"
#include <aggregates_to_tuples.hpp>


namespace {
    struct person {
        float const size;
        int age;
    };
}

TEST_CASE("basics") {
    person p{ 1.75f, 24 };
    auto tuple = to_tuple(p);
    auto tuple_refs = as_tuple(p);

    p.age += 2;
    REQUIRE(std::get<1>(tuple) == 24);
    REQUIRE(std::get<1>(tuple_refs) == 26);
}
