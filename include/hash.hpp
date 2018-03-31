
/// Defines the function att::hash for aggregates.

#pragma once

#include <core.hpp>
#include <functional>

namespace att {

    /// The default function used to combine hashes.

    using hash_combiner_t = size_t (*) (size_t, size_t);

    size_t default_hash_combiner(size_t seed, size_t hash) {
        return seed ^ hash + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    /// Check if a type has a std hash function.

    namespace detail {
        namespace impl {
            template <class T>
            using hash_expr = decltype(
                std::declval<std::hash<T>>()(std::declval<T const&>())
            );
        }
        template <class T>
        constexpr bool has_hash = is_detected<impl::hash_expr, T>;
    }

    namespace detail {

        /// Forward declaration of the first recursive function.
        
        template <class T, class = std::enable_if_t<
            detail::has_hash<T> || is_aggregate<T>
        >>
        size_t hash_val(T const& val, size_t seed, hash_combiner_t combiner);

        /// The second recursive function, acting on tuples.

        template <int I, class...Ts>
        size_t hash_tuple(
                std::tuple<Ts...>& tuple,
                size_t seed,
                hash_combiner_t combiner,
                value_tag<int, I>)
        {
            if constexpr (I == sizeof...(Ts)) {
                return seed;
            }
            else {
                auto const& val = std::get<I>(tuple);
                return hash_tuple(
                    tuple,
                    hash_val(val, seed, combiner),
                    combiner,
                    value_tag<int, I + 1>{});
            }
        }

        /// The first recursive function implementation.

        template <class T, class SFINAE>
        size_t hash_val(T const& val, size_t seed, hash_combiner_t combiner) {
            if constexpr (detail::has_hash<T>) {
                return combiner(seed, std::hash<T>{}(val));
            }
            else { // T is aggregate
                return hash_tuple(
                    as_tuple(val),
                    seed,
                    combiner,
                    value_tag<int, 0>{});
            }
        }

    }

    /// The public hash function.

    template <class T, class = std::enable_if_t<
        detail::has_hash<T> || is_aggregate<T>
    >>
    size_t hash(T const& val, hash_combiner_t combiner = default_hash_combiner) {
        return detail::hash_val(val, 0, combiner);
    }

}
