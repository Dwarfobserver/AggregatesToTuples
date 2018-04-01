
/// Defines for_each and for_each recursively functions.

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

    /// Helper type to make predicates easily.

    namespace impl {
        template <template <class> class Expression>
        struct predicate {
            template <class T>
            struct type {
                static constexpr bool value = detail::is_detected<Expression, T>;
            };
        };
    }

    /// Helper function to pass a predicate to a function, based to the validity of an expression.

    template <template <class> class Expression>
    constexpr auto make_predicate() {
        using Predicate = impl::predicate<Expression>;
        using Tag = detail::hightype_tag<Predicate::template type>;
        return Tag {};
    }

    /// Helper function to pass a predicate to a function, which matches types to booleans (with Predicate<T>::value).

    template <template <class> class Predicate>
    constexpr auto pass_predicate() {
        return detail::hightype_tag<Predicate>{};
    }

    /// Forward declaration of for_each_recursively.
    /// Predicate matches types to booleans with Predicate<T>::value.
    /// The boolean indicates if the function can be called on the type.

    template <class T, class F, template <class> class Predicate>
    void for_each_recursively(T& data, F&& f, detail::hightype_tag<Predicate>);
    
    namespace impl {

        /// Looping on tuples.

        template <class F, template <class> class Predicate, int I, class...Ts>
        void for_each_tuple_recursively(
                std::tuple<Ts...>& tuple,
                F&& f,
                detail::value_tag<int, I>,
                detail::hightype_tag<Predicate> tag)
        {
            if constexpr (I < sizeof...(Ts)) {
                for_each_recursively(std::get<I>(tuple), f, tag);
                for_each_tuple_recursively(tuple, f, detail::value_tag<int, I + 1>{}, tag);
            }
        }

    }

    /// for_each_recursively implementation.

    template <class T, class F, template <class> class Predicate>
    void for_each_recursively(T& data, F&& f, detail::hightype_tag<Predicate> tag) {
        if constexpr (Predicate<T>::value) {
            f(data);
        }
        else if constexpr (is_aggregate<T>) {
            auto refs = att::as_tuple(data);
            impl::for_each_tuple_recursively(refs, f, detail::value_tag<int, 0>{}, tag);
        }
        else {
            static_assert(Predicate<T>::value,
            "T must be an aggregate, or the predicate for T must be true");
        }
    }

}
