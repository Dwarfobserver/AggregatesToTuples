
#include "catch.hpp"
#include <hash.hpp>


namespace {
    struct info {
        float const size;
        int age;
    };
    struct person {
        std::string name;
        info i;
    };
}

TEST_CASE("hashes") {
    person alice { "Alice", { 1.63f, 22 } };
    person bob   { "Bob"  , { 1.81f, 21 } };

    CHECK(att::hash(alice) != att::hash(bob));

    auto bob2 = bob;
    CHECK(att::hash(bob) == att::hash(bob2));

    bob2.i.age += 1;
    CHECK(att::hash(bob) != att::hash(bob2));

    CHECK(att::hash(alice, [] (size_t seed, size_t hash) {
        return seed + 1;
    }) == 3);
}
