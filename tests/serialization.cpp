
#include "catch.hpp"
#include <serialization.hpp>
#include <sstream>

namespace {
    struct person {
        std::string name;
        int age;
    };
}

TEST_CASE("ostream serialization") {
    person alice = { "Alice", 32 };
    person bob   = { "Bob"  , 47 };

    std::ostringstream ostream;

    using namespace att::operators;

    ostream << alice << bob;

    CHECK(ostream.str() == "Alice32Bob47");

    person unknown;

    std::stringstream stream;
    stream << "Brown 68";

    stream >> unknown;

    CHECK(unknown.name == "Brown");
    CHECK(unknown.age  == 68);
}
