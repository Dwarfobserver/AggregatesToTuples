
#include "catch.hpp"
#include <equality.hpp>
#include <string>

namespace {
    struct person {
        float const size;
        int age;
    };
    struct team {
        std::string name;
        person warrior;
        person support;
    };
}

TEST_CASE("equality tests") {
    person warrior = { 1.88f, 32 };
    person support = { 1.74f, 47 };

    CHECK( att::test_equality(warrior, warrior));
    CHECK(!att::test_equality(warrior, support));

    team goblins   = { "goblins", warrior, support };
    team halflings = goblins;

    CHECK(att::test_equality(goblins, halflings));
    
    halflings.warrior.age += 1;

    CHECK(!att::test_equality(goblins, halflings));
}
