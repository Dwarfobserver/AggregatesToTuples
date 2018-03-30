
#include "catch.hpp"
#include <core.hpp>


namespace {
    struct person {
        float const size;
        int age;
    };
    class wrapper {
        int value;
    public:
        wrapper(int v) : value(v) {}
    };
}

TEST_CASE("constexpr traits") {
    CHECK( att::is_aggregate<person>);
    CHECK(!att::is_aggregate<wrapper>);

    CHECK( att::arity_of<person> == 2);
}

TEST_CASE("core functions and types") {
    person p{ 1.75f, 24 };
    auto tuple = att::to_tuple(p);
    auto tuple_refs = att::as_tuple(p);

    p.age += 2;
    CHECK(std::get<1>(tuple) == 24);
    CHECK(std::get<1>(tuple_refs) == 26);

    att::to_tuple_t<person> tuple2 = tuple_refs;
    std::get<1>(tuple2) += 1;
    CHECK(p.age == 26);

    att::as_tuple_t<person> tuple_refs2 = tuple_refs;
    std::get<1>(tuple_refs2) += 1;
    CHECK(p.age == 27);
}
