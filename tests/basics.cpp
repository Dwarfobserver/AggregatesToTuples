
#include "catch.hpp"
#include <aggregates_to_tuples.hpp>


namespace {
    struct person {
        float const size;
        int age;
    };
    class wrapper {
        int value;
        wrapper(int v) : value(v) {}
    };
}

TEST_CASE("constexpr values") {
    static_assert( traits::is_aggregate<person>);
    static_assert(!traits::is_aggregate<wrapper>);

    static_assert(traits::arity_of<person> == 2);
}

TEST_CASE("core functions and types") {
    person p{ 1.75f, 24 };
    auto tuple = to_tuple(p);
    auto tuple_refs = as_tuple(p);

    p.age += 2;
    REQUIRE(std::get<1>(tuple) == 24);
    REQUIRE(std::get<1>(tuple_refs) == 26);

    tuple_type_of<person> tuple2 = tuple_refs;
    std::get<1>(tuple2) += 1;
    REQUIRE(p.age == 26);

    tuple_ref_type_of<person> tuple_refs2 = tuple_refs;
    std::get<1>(tuple_refs2) += 1;
    REQUIRE(p.age == 27);
}
