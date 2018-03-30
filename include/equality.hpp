
#pragma once

#include <core.hpp>

namespace att {

    /// Check if equality is detected for a type.

    namespace detail {
        template <class T>
        using equality_expr = decltype(
            std::declval<T const&>() == std::declval<T const&>()
        );
        template <class T>
        constexpr bool has_equality = is_detected<equality_expr, T>;
    }

    /// Equality forward declaration;

    template <class T, class = std::enable_if_t<
        detail::has_equality<T> || is_aggregate<T>
    >>
    bool test_equality(T const& lhs, T const& rhs);

    /// Test equality of tuples recursively.

    namespace detail {
        template <int I, class...Ts>
        bool test_equality_tuple(
                std::tuple<Ts...> const& lhs,
                std::tuple<Ts...> const& rhs,
                value_tag<I>)
        {
            if constexpr (I == sizeof...(Ts)) {
                return true;
            }
            else {
                return test_equality(std::get<I>(lhs), std::get<I>(rhs)) &&
                    test_equality_tuple(lhs, rhs, value_tag<I + 1>{});
            }
        }
    }

    /// Equality implementation.

    template <class T, class SFINAE>
    bool test_equality(T const& lhs, T const& rhs) {
        if constexpr (detail::has_equality<T>) {
            return lhs == rhs;
        }
        else { // T is aggregate
            return detail::test_equality_tuple(
                as_tuple(lhs),
                as_tuple(rhs),
                detail::value_tag<0>{});
        }
    }

}
