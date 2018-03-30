
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

TEST_CASE("equality") {
    person warrior = { 1.88f, 32 };
    person support = { 1.74f, 47 };

    using namespace att::operators;

    bool WeqW = warrior == warrior;
    bool WneqS = warrior != support;
    CHECK(WeqW);  // Can't check equality directly, because
    CHECK(WneqS); // Catch internally expand the equality.

    team goblins   = { "goblins", warrior, support };
    team halflings = goblins;

    bool GeqH = goblins == halflings;
    CHECK(GeqH);
    
    halflings.warrior.age += 1;

    bool GneqH = goblins != halflings;
    CHECK(GneqH);
}
