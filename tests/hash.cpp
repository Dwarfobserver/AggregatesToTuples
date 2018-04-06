
#include "catch.hpp"
#include <hash.hpp>
#include <comparisons.hpp>
#include <unordered_set>

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

    auto combiner = [] (size_t seed, size_t hash) {
        return seed + 1;
    };
    CHECK(att::hash(alice, combiner) == 3);
}

TEST_CASE("hash functor") {
    using hasher   = att::hash_functor<info>;
    using comparer = att::equality_functor<info>;
    std::unordered_set<info, hasher, comparer> set;

    set.insert({ 1.62f, 39 });

    CHECK(set.find({ 1.62f, 12 }) == set.end());
    CHECK(set.find({ 1.62f, 39 }) != set.end());
}
