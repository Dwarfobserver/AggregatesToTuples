
#include "catch.hpp"
#include <hash.hpp>


namespace {
    struct person {
        std::string name;
        float const size;
        int age;
    };
}

TEST_CASE("hashes") {
    person alice { "Alice", 1.63f, 22 };
    person bob   { "Bob"  , 1.81f, 21 };

    CHECK(att::hash(alice) != att::hash(bob));

    auto bob2 = bob;
    CHECK(att::hash(bob) == att::hash(bob2));

    bob2.age += 1;
    CHECK(att::hash(bob) != att::hash(bob2));
}
