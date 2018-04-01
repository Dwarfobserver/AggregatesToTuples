
#include "catch.hpp"
#include <core.hpp>
#include <memory>
#include <string>

namespace {
    struct person {
        std::string name;
        float const size;
        int age;
    };
    class wrapper {
        int value;
    public:
        wrapper(int v) : value(v) {}
    };
    struct movable {
        std::unique_ptr<int> ptr;
    };
}

TEST_CASE("constexpr traits") {
    CHECK(!att::is_aggregate<wrapper>);
    CHECK( att::is_aggregate<person>);
    CHECK( att::is_aggregate<movable>);

    CHECK(att::arity_of<person>  == 3);
    CHECK(att::arity_of<movable> == 1);
}

TEST_CASE("core functions and types") {
    person p{ "Brown", 1.75f, 24 };

    auto tuple = att::to_tuple(p);
    auto tuple_refs = att::as_tuple(p);

    p.age += 2;
    CHECK(std::get<2>(tuple) == 24);
    CHECK(std::get<2>(tuple_refs) == 26);

    att::to_tuple_t<person> tuple2 = tuple_refs;
    std::get<0>(tuple2) += " !";
    CHECK(p.name == "Brown");

    att::as_tuple_t<person> tuple_refs2 = tuple_refs;
    std::get<0>(tuple_refs2) += " !";
    CHECK(p.name == "Brown !");
}

TEST_CASE("make tuple by move") {
    movable m{ std::make_unique<int>(42) };

    auto tuple_refs = att::as_tuple(m);
    auto tuple = att::to_tuple(std::move(m));

    CHECK(m.ptr.get() == nullptr);

    auto& ptr = std::get<0>(tuple);
    CHECK(*ptr == 42);
}
