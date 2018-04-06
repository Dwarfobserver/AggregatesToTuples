
/// Defines the function att::hash for aggregates, with it's functor att::hash_functor<T>.

#pragma once

#include <loops.hpp>
#include <functional>

namespace att {

    /// The default function used to combine hashes.

    using hash_combiner_t = size_t (*) (size_t, size_t);

    constexpr size_t default_hash_combiner(size_t seed, size_t hash) {
        return seed ^ hash + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    /// The expression which detects if a type can be hashed.
    
    namespace impl {
        template <class T>
        using hash_expr = decltype(
            std::declval<std::hash<std::remove_cv_t<T>>>()(std::declval<T const&>())
        );
    }

    /// Public function, using for_each_recursively.

    template <class T>
    constexpr size_t hash(T const& data, hash_combiner_t combiner = default_hash_combiner) {
        constexpr auto tag = make_predicate<impl::hash_expr>();
        size_t seed = 0;
        for_each_recursively(data, tag, [&] (auto const& val)
        {
            using ValueT = typename std::remove_cv_t<std::remove_reference_t<decltype(val)>>;
            seed = combiner(seed, std::hash<ValueT>{}(val));
        });
        return seed;
    }

    /// Hash functor. Can be used for exemple to provide the function to standard containers.

    template <class T, hash_combiner_t combiner = default_hash_combiner>
    struct hash_functor {
        constexpr size_t operator()(T const& val) const {
            return hash(val, combiner);
        }
    };

}
