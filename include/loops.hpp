
/// Defines for_each and for_each_recursively functions.

#pragma once

#include <core.hpp>

namespace att {

    /// for_each which applies f recursively on a tuple.

    namespace impl {
        
        template <class F, int I, class...Ts>
        void for_each_tuple(std::tuple<Ts...>& tuple, F&& f, detail::value_tag<int , I>) {
            if constexpr (I < sizeof...(Ts)) {
                f(std::get<I>(tuple));
                for_each_tuple(tuple, f, detail::value_tag<int, I + 1>{});
            }
        }
    }

    /// for_each for aggregates.

    template <class T, class F, class = std::enable_if_t<
        is_aggregate<T>
    >>
    void for_each(T&& aggregate, F&& f) {
        auto refs = as_tuple(aggregate);
        impl::for_each_tuple(refs, f, detail::value_tag<int, 0>{});
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

    /// Forward declaration of for_each_recursively.
    /// Predicate matches types to booleans with Predicate<T>::value.
    /// The boolean indicates if the function can be called on the type.

    template <class T, template <class> class Predicate, class F>
    void for_each_recursively(T& data, predicate_tag<Predicate> predicate, F&& f);
    
    namespace impl {

        /// Looping on tuples.

        template <template <class> class Predicate, class F, int I, class...Ts>
        void for_each_tuple_recursively(
                std::tuple<Ts...>& tuple,
                F&& f,
                detail::value_tag<int, I>,
                predicate_tag<Predicate> predicate)
        {
            if constexpr (I < sizeof...(Ts)) {
                for_each_recursively(std::get<I>(tuple), predicate, f);
                for_each_tuple_recursively(tuple, f, detail::value_tag<int, I + 1>{}, predicate);
            }
        }

    }

    /// for_each_recursively implementation.

    template <class T, template <class> class Predicate, class F>
    void for_each_recursively(T& data, predicate_tag<Predicate> predicate, F&& f) {
        if constexpr (Predicate<T>::value) {
            f(data);
        }
        else if constexpr (is_aggregate<T>) {
            auto refs = as_tuple(data);
            impl::for_each_tuple_recursively(refs, f, detail::value_tag<int, 0>{}, predicate);
        }
        else {
            static_assert(Predicate<T>::value,
            "T must be an aggregate, or the predicate for T must be true");
        }
    }

}
