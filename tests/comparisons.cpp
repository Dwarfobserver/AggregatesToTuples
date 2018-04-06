
#include "catch.hpp"
#include <comparisons.hpp>
#include <string>
#include <set>

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

TEST_CASE("equality") {
    person warrior = { 1.88f, 32 };
    person support = { 1.74f, 47 };

    using comparer = att::equality_functor<person>;

    CHECK( comparer{}(warrior, warrior));  
    CHECK(!comparer{}(warrior, support));

    team goblins   = { "goblins", warrior, support };
    team halflings = goblins;

    using namespace att::operators;

    // Can't check equality directly, because Catch internally expand
    // the equality (without the namespace att::operators).
    bool GeqH = goblins == halflings; 
    CHECK(GeqH);
    
    halflings.warrior.age += 1;

    bool GneqH = goblins != halflings;
    CHECK(GneqH);
}

TEST_CASE("less operator") {
    person warrior = { 1.88f, 32 };
    person support = { 1.74f, 47 };

    using namespace att::operators;

    bool WnltW = warrior >= warrior;
    bool WltW = warrior > warrior;
    bool SltW = support < warrior;
    CHECK(WnltW); // Same as for the equality
    CHECK(!WltW);
    CHECK(SltW);

    team goblins   = { "goblins", warrior, support };
    team halflings = goblins;

    bool HnltG = goblins <= halflings;
    bool HltG = halflings < goblins;
    CHECK(HnltG);
    CHECK(!HltG);
    
    halflings.warrior.age += 1;

    bool GltH = goblins < halflings;
    CHECK(GltH);
}

TEST_CASE("less functor") {
    using orderer = att::less_functor<person>;
    std::set<person, orderer> set;

    set.insert({ 1.62f, 39 });

    CHECK(set.find({ 1.62f, 12 }) == set.end());
    CHECK(set.find({ 1.62f, 39 }) != set.end());
}

