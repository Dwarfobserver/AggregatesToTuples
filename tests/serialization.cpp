
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

namespace {
    struct number_serializer {
        int* buffer;

        number_serializer& operator<<(int i) {
            *(buffer++) = i;
            return *this;
        }
        number_serializer& operator>>(int& i) {
            i = *(buffer++);
            return *this;
        }
    };
    struct info_pack {
        info i1;
        info i2;
        info i3;
    };
}


TEST_CASE("custom serialization") {
    int buffer[10];

    info_pack const infos = { { 1, 2 }, { 3, 4 }, { 5, 6 } };

    number_serializer stream { buffer };
    using namespace att::operators;

    stream << infos;

    info_pack infos_copy = {};

    stream.buffer = buffer;
    stream >> infos_copy;

    CHECK(infos.i1.size == infos_copy.i1.size);
    CHECK(infos.i3.age  == infos_copy.i3.age);
}
