
#pragma once

#include <core.hpp>

namespace att {

    /// Check if equality is detected for a type.

    namespace detail {
        namespace impl {
            template <class T>
            using equality_expr = decltype(
                std::declval<T const&>() == std::declval<T const&>()
            );
        }
        template <class T>
        constexpr bool has_equality = is_detected<impl::equality_expr, T>;
    }

    /// Equality forward declaration;

    namespace operators {
        template <class T, class = std::enable_if_t<
            detail::has_equality<T> || is_aggregate<T>
        >>
        bool operator==(T const& lhs, T const& rhs);
    }

    /// Test equality of tuples recursively.

    namespace impl {
        template <int I, class...Ts>
        bool test_equality_tuple(
                std::tuple<Ts...> const& lhs,
                std::tuple<Ts...> const& rhs,
                detail::value_tag<int, I>)
        {
            if constexpr (I == sizeof...(Ts)) {
                return true;
            }
            else {
                using namespace att::operators;
                return (std::get<I>(lhs) == std::get<I>(rhs)) &&
                    test_equality_tuple(lhs, rhs, detail::value_tag<int, I + 1>{});
            }
        }
    }

    /// Equality implementation.

    namespace operators {
        template <class T, class SFINAE>
        bool operator==(T const& lhs, T const& rhs) {
            if constexpr (detail::has_equality<T>) {
                return lhs == rhs;
            }
            else { // T is aggregate
                return impl::test_equality_tuple(
                    as_tuple(lhs),
                    as_tuple(rhs),
                    detail::value_tag<int, 0>{});
            }
        }

        /// The opposite operator.
        
        template <class T, class = std::enable_if_t<
            detail::has_equality<T> || is_aggregate<T>
        >>
        bool operator!=(T const& lhs, T const& rhs) {
            return !(lhs == rhs);
        }
    }

}
