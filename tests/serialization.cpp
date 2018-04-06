
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

    CHECK(ostream.str() == "{ Alice , { 32 , 176 } }"
                             "{ Bob , { 24 , 183 } }");

    person unknown;

    std::stringstream stream;
    stream << "{ Brown , { 68 , 182 } }";

    stream >> unknown;

    CHECK(unknown.name   == "Brown");
    CHECK(unknown.i.age  == 68);
    CHECK(unknown.i.size == 182);
}

namespace {
    struct number_serializer { /// How serialization could be implemented :
        int* buffer;

        /// The operation implementations.

        void serialize(int i) {
            *(buffer++) = i;
        }
        void deserialize(int& i) {
            i = *(buffer++);
        }

        /// The expressions which make predicates.

        template <class T>
        using serialize_expr = decltype(
            std::declval<number_serializer&>().serialize(std::declval<T const&>())
        );

        template <class T>
        using deserialize_expr = decltype(
            std::declval<number_serializer&>().deserialize(std::declval<T&>())
        );

        /// The public operators.

        template <class T>
        number_serializer& operator<<(T const& data) {
            constexpr auto predicate = att::make_predicate<serialize_expr>();
            att::for_each_recursively(data, predicate, [this] (auto&& val) {
                serialize(val);
            });
            return *this;
        }

        template <class T>
        number_serializer& operator>>(T& data) {
            constexpr auto predicate = att::make_predicate<deserialize_expr>();
            att::for_each_recursively(data, predicate, [this] (auto&& val) {
                deserialize(val);
            });
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

    stream << infos;

    info_pack infos_copy = {};

    stream.buffer = buffer;
    stream >> infos_copy;

    CHECK(infos.i1.size == infos_copy.i1.size);
    CHECK(infos.i3.age  == infos_copy.i3.age);
}
