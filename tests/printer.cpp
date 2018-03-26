
#include "catch.hpp"
#include <aggregates_to_tuples.hpp>
#include <sstream>

template <class F, int I, class...Ts>
void visit_tuple_rec(std::tuple<Ts...> const& t, F&& f, att::traits::value_tag<I>) {
    if constexpr (I < sizeof...(Ts)) {
        f(std::get<I>(t));
        visit_tuple_rec(t, f, att::traits::value_tag<I + 1>{});
    }
}

template <class F, class...Ts>
void visit_tuple(std::tuple<Ts...> const& t, F&& f) {
    visit_tuple_rec(t, f, att::traits::value_tag<0>{});
}

template <class...Ts>
std::ostream& operator<<(std::ostream& stream, std::tuple<Ts...> const& tuple) {
    stream << '{';
    visit_tuple(tuple, [&stream] (auto&& value) {
        stream << ' ' << value;
    });
    return stream << " }";
}

namespace {
    struct person {
        std::string name;
        int age;
    };
}

TEST_CASE("printer") {
    std::ostringstream stream;

    person p{ "Alex", 24 };
    stream << att::as_tuple(p);

    REQUIRE(stream.str() == "{ Alex 24 }");
}
