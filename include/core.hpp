
/// Defines the core functions as_tuple, to_tuple and from_tuple.

#pragma once

#include <tools.hpp>
#include <tuple>

#include <arity_functions.inl>

namespace att {

    /// Detects if a type is brace-constructible from N elements.

    namespace detail {
        namespace impl {
            template <class SFINAE, class T, class...Args>
            struct is_brace_constructible {
                static constexpr bool value = false;
            };

            template <class T, class...Args>
            struct is_brace_constructible<std::void_t<decltype(
                T{ any<Args>... }
            )>, T, types_tag<Args...>> {
                static constexpr bool value = true;
            };
        }

        template <class T, unsigned N>
        constexpr bool is_brace_constructible =
            impl::is_brace_constructible<void, T, make_types_tag<N, void>>::value;
    }

    /// Detects if a type is parenthesis-constructible from N elements.

    namespace detail {
        namespace impl {
            template <class SFINAE, class T, class...Args>
            struct is_parenthesis_constructible {
                static constexpr bool value = false;
            };

            template <class T, class...Args>
            struct is_parenthesis_constructible<std::void_t<
                decltype(T( any<Args>... ))
            >, T, types_tag<Args...>> {
                static constexpr bool value = true;
            };
        }

        template <class T, unsigned N>
        constexpr bool is_parenthesis_constructible =
            impl::is_parenthesis_constructible<void, T, make_types_tag<N, void>>::value;
    }

    /// Detects if a type is parenthesis-constructible from one element.
    /// Discards copy and move constructors.
        
    namespace detail {
        namespace impl {
            template <class SFINAE, class T>
            struct is_one_arg_constructible {
                static constexpr bool value = false;
            };

            template <class T>
            struct is_one_arg_constructible<std::void_t<
                decltype(T( std::declval<wildcard_except<T>>() ))
            >, T> {
                static constexpr bool value = true;
            };
        }

        template <class T>
        constexpr bool is_one_arg_constructible =
            impl::is_one_arg_constructible<void, T>::value;
    }

    /// Check if a type must be manually discarded from the aggregate detection.

    namespace detail {

        template <class T>
        constexpr bool is_aggregate_exception =
            std::is_fundamental_v<T> ||
            std::is_pointer_v<T>     ||
            std::is_union_v<T>;
    }

    /// Gives the arity of a type (the number of elements which construct him).
    /// If he isn't an aggregate type, returns -1.
    /// If the maximum arity is reached, stops the compilation.

    namespace impl {

        template <class T, int I>
        constexpr int arity_of_rec() {
            if constexpr (detail::is_parenthesis_constructible<T, I>) {
                return -1;
            }
            else if constexpr (!detail::is_brace_constructible<T, I>) {
                return I - 1;
            }
            else {
                return arity_of_rec<T, I + 1>();
            }
        }

        template <class T>
        constexpr int arity_of() {
            constexpr bool discarded = detail::is_aggregate_exception<T>    ||
                                      !detail::is_brace_constructible<T, 0> ||
                                       detail::is_one_arg_constructible<T>  ||
                                       detail::is_brace_constructible<T, max_arity + 1>;

            if constexpr (discarded) {
                return -1;
            }
            else if constexpr (!detail::is_brace_constructible<T, 1>) {
                return 0;
            }
            else {
                return arity_of_rec<T, 2>();
            }
        }

    }

    template <class T>
    constexpr int arity_of = impl::arity_of<std::remove_reference_t<T>>();

    /// Helper value which indicates if a type is an aggregate.

    template <class T>
    constexpr bool is_aggregate = arity_of<T> != -1;

    /// Makes a tuple of references on the given aggregate.

    template <class Aggregate, class = std::enable_if_t<
        is_aggregate<Aggregate>
    >>
    constexpr auto as_tuple(Aggregate& aggregate) noexcept {
        constexpr int arity = arity_of<Aggregate>;
        return detail::as_tuple_impl(aggregate, detail::value_tag<int, arity>{});
    }

    /// Copies the given aggregate as a tuple.

    template <class Aggregate, class = std::enable_if_t<
        is_aggregate<std::remove_reference_t<Aggregate>>
    >>
    constexpr auto to_tuple(Aggregate&& aggregate)
        noexcept(!std::is_reference_v<Aggregate> && std::is_nothrow_move_constructible_v<Aggregate>)
    {
        constexpr int arity = arity_of<std::remove_reference_t<Aggregate>>;
        return detail::to_tuple_impl(std::forward<Aggregate>(aggregate), detail::value_tag<int, arity>{});
    }

    /// The return type of as_tuple.

    template <class Aggregate>
    using as_tuple_t = typename std::remove_reference_t<decltype(
        as_tuple(std::declval<Aggregate&>())
    )>;

    /// The return type of to_tuple.

    template <class Aggregate>
    using to_tuple_t = typename std::remove_reference_t<decltype(
        to_tuple(std::declval<Aggregate>())
    )>;

    /// From tuple with out parameter, with copy and move versions.

    template <class Aggregate, class...Ts, class = std::enable_if_t<
        is_aggregate<Aggregate>
    >>
    constexpr void from_tuple(std::tuple<Ts...> const& tuple, Aggregate& aggregate) {
        auto refs = as_tuple(aggregate);
        refs = tuple;
    }
    
    template <class Aggregate, class...Ts, class = std::enable_if_t<
        is_aggregate<Aggregate>
    >>
    constexpr void from_tuple(std::tuple<Ts...>&& tuple, Aggregate& aggregate)
        noexcept(std::is_nothrow_move_constructible_v<std::tuple<Ts...>>)
    {
        auto refs = as_tuple(aggregate);
        refs = std::move(tuple);
    }

    /// From tuple proxy objects which creates the aggregate.

    namespace detail {

        /// Copy version.

        template <class...Ts>
        struct tuple_copy_proxy {
            constexpr tuple_copy_proxy(std::tuple<Ts...> const& tuple) noexcept : tuple(tuple) {}
        private:
            std::tuple<Ts...> const& tuple;

            template <class Aggregate, size_t...Is>
            constexpr Aggregate make_impl(type_tag<Aggregate>, std::index_sequence<Is...>) {
                return Aggregate { std::get<Is>(tuple) ... };
            };
        public:
            template <class Aggregate, class = std::enable_if_t<
                is_aggregate<Aggregate>
            >>
            constexpr Aggregate make() {
                return make_impl(type_tag<Aggregate>{}, std::index_sequence_for<Ts...>{});
            };
        };
        
        /// Move version.

        template <class...Ts>
        struct tuple_move_proxy {
            constexpr tuple_move_proxy(std::tuple<Ts...>&& tuple) noexcept : tuple(tuple) {}
        private:
            std::tuple<Ts...>& tuple;

            template <class Aggregate, size_t...Is>
            constexpr Aggregate make_impl(type_tag<Aggregate>, std::index_sequence<Is...>) {
                return Aggregate { std::move(std::get<Is>(tuple)) ... };
            };
        public:
            template <class Aggregate, class = std::enable_if_t<
                is_aggregate<Aggregate>
            >>
            constexpr Aggregate make() 
                noexcept(std::is_nothrow_move_constructible_v<std::tuple<Ts...>>)
            {
                return make_impl(type_tag<Aggregate>{}, std::index_sequence_for<Ts...>{});
            };
        };

    }

    /// From tuples with their proxies, with copy and move versions.

    template <class...Ts>
    constexpr auto from_tuple(std::tuple<Ts...> const& tuple) noexcept {
        return detail::tuple_copy_proxy<Ts...>{ tuple };
    }
    
    template <class...Ts>
    constexpr auto from_tuple(std::tuple<Ts...>&& tuple) noexcept {
        return detail::tuple_move_proxy<Ts...>{ std::move(tuple) };
    }

}
