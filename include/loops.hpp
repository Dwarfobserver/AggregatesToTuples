
/// Defines for_each and for_each_recursively functions.

#pragma once

#include <core.hpp>

namespace att {

    /// for_each for aggregates.

    template <class Aggregate, class F, class = std::enable_if_t<
        is_aggregate<Aggregate>
    >>
    constexpr void for_each(Aggregate&& aggregate, F&& f) {
        std::apply([&f] (auto&&...args) {
            (f(std::forward<decltype(args)>(args)), ...);
        }, as_tuple(aggregate));
    }

    /// Helper type to make predicates easily based on an expression.
    /// A predicate is a template type which matches types to booleans (with Predicate<T>::value).

    namespace impl {
        template <template <class> class Expression>
        struct predicate {
            template <class T>
            struct type {
                static constexpr bool value = detail::is_detected<Expression, T>;
            };
        };
    }

    /// Helper alias for predicate types.

    template <template <class> class Predicate>
    using predicate_tag = detail::hightype_tag<Predicate>;

    /// Helper function to create and pass a predicate to a function based to the validity of an expression.

    template <template <class> class Expression>
    constexpr auto make_predicate() noexcept {
        using Predicate = impl::predicate<Expression>;
        using Tag = predicate_tag<Predicate::template type>;
        return Tag {};
    }

    /// for_each_recursively implementation.
    /// The predicate indicates if the function can be called on the type.

    template <class T, template <class> class Predicate, class F>
    constexpr void for_each_recursively(T& data, predicate_tag<Predicate>, F&& f) {
        
        static_assert(Predicate<T>::value || is_aggregate<T>,
            "T must be an aggregate, or the predicate for T must be true");

        if constexpr (Predicate<T>::value) {
            f(data);
        }
        else { // T is aggregate
            for_each(data, [&f] (auto&& arg) {
                for_each_recursively(arg, predicate_tag<Predicate>{}, f);
            });
        }
    }

}
