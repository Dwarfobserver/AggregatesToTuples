
#include "catch.hpp"
#include <serialization.hpp>
#include <sstream>

namespace {
    struct info {
        int age;
        int size;
    };
    struct person {
        std::string name;
        info i;
    };
}

TEST_CASE("ostream serialization") {
    person alice = { "Alice", { 32, 176 } };
    person bob   = { "Bob"  , { 24, 183 } };

    std::ostringstream ostream;

    using namespace att::operators;

    ostream << alice << bob;

    CHECK(ostream.str() == "Alice""32""176"
                           "Bob"  "24""183");

    person unknown;

    std::stringstream stream;
    stream << "Brown 68 182";

    stream >> unknown;

    CHECK(unknown.name   == "Brown");
    CHECK(unknown.i.age  == 68);
    CHECK(unknown.i.size == 182);
}
