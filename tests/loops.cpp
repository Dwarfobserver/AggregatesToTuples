
#include "catch.hpp"
#include <loops.hpp>

namespace {
    struct arm {
        int thumb;
        int pinky;
    };
    struct humanoint {
        arm leftArm;
        int head;
        arm rightArm;
    };

    template <class T>
    struct predicate {
        static constexpr bool value = false;
    };
    template <>
    struct predicate<int> {
        static constexpr bool value = true;
    };
    template <>
    struct predicate<int const> {
        static constexpr bool value = true;
    };
}

TEST_CASE("loops") {
    humanoint const h { { 1, 2 }, 3, { 4, 5 } };

    int members = 0;
    att::for_each(h, [&] (auto const&) {
        members += 1;
    });
    CHECK(members == 3);
    
    constexpr auto tag = att::predicate_tag<predicate>{};
    int sum = 0;
    att::for_each_recursively(h, tag, [&] (int val) {
        sum += val;
    });
    CHECK(sum == 15);
}
