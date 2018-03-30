
#pragma once

#include <utils.hpp>
#include <tuple>

namespace att {

    /// Defines the max arity that a type can have.
    /// This size can be increased if as_tuple and to_tuple functions for a greater arity are provided.

    constexpr int max_arity = 20;

    /// Detects if a type is brace-constructible from N elements.

    namespace detail {
        namespace detail {
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
            detail::is_brace_constructible<void, T, make_types_tag<N, void>>::value;
    }

    /// Detects if a type is parenthesis-constructible from N elements.

    namespace detail {
        namespace detail {
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
            detail::is_parenthesis_constructible<void, T, make_types_tag<N, void>>::value;
    }

    /// Detects if a type is parenthesis-constructible from one element.
    /// Discards copy and move constructors.
        
    namespace detail {
        namespace detail {
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
            detail::is_one_arg_constructible<void, T>::value;
    }

    /// Gives the arity of a type (the number of elements which construct him).
    /// If he isn't an aggregate type, returns -1.
    /// If the maximum arity is reached, stops the compilation.

    namespace detail {

        template <class T, int I>
        constexpr int arity_of_rec() {
            if constexpr (is_parenthesis_constructible<T, I>) {
                return -1;
            }
            else if constexpr (!is_brace_constructible<T, I>) {
                return I - 1;
            }
            else {
                return arity_of_rec<T, I + 1>();
            }
        }

        template <class T>
        constexpr int arity_of() {
            if constexpr (!is_brace_constructible<T, 0> ||
                is_brace_constructible<T, max_arity + 1>)
            {
                return -1;
            }
            else if constexpr (is_one_arg_constructible<T>) {
                return -1;
            }
            else if constexpr (!is_brace_constructible<T, 1>) {
                return 0;
            }
            else {
                return arity_of_rec<T, 2>();
            }
        }

    }

    template <class T>
    constexpr int arity_of = detail::arity_of<T>();

    /// Helper value which indicates if a type is an aggregate.

    template <class T>
    constexpr bool is_aggregate = arity_of<T> != -1;

    namespace detail {

        /// Dispatched functions to make tuples based on the aggregate arity.

        template <class Aggregate, int Arity>
        auto as_tuple(Aggregate& aggregate, value_tag<Arity>);
        template <class Aggregate, int Arity>
        auto to_tuple(Aggregate&& aggregate, value_tag<Arity>);

        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<0>) {
            return std::make_tuple();
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<0>) {
            return std::make_tuple();
        }

        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<1>) {
            auto& [v1] = aggregate;
            return std::forward_as_tuple(v1);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<1>) {
            auto&& [v1] = aggregate;
            return std::make_tuple(v1);
        }

        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<2>) {
            auto& [v1, v2] = aggregate;
            return std::forward_as_tuple(v1, v2);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<2>) {
            auto&& [v1, v2] = aggregate;
            return std::make_tuple(v1, v2);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<3>) {
            auto& [v1, v2, v3] = aggregate;
            return std::forward_as_tuple(v1, v2, v3);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<3>) {
            auto&& [v1, v2, v3] = aggregate;
            return std::make_tuple(v1, v2, v3);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<4>) {
            auto& [v1, v2, v3, v4] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<4>) {
            auto&& [v1, v2, v3, v4] = aggregate;
            return std::make_tuple(v1, v2, v3, v4);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<5>) {
            auto& [v1, v2, v3, v4, v5] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<5>) {
            auto&& [v1, v2, v3, v4, v5] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<6>) {
            auto& [v1, v2, v3, v4, v5, v6] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<6>) {
            auto&& [v1, v2, v3, v4, v5, v6] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<7>) {
            auto& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<7>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<8>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<8>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<9>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<9>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<10>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<10>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<11>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<11>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<12>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<12>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<13>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<13>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<14>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<14>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<15>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<15>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<16>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<16>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<17>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<17>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<18>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<18>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<19>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<19>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, value_tag<20>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, value_tag<20>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
        }
    }

    /// Makes a tuple of references on the given aggregate.

    template <class Aggregate, class = std::enable_if_t<
        is_aggregate<Aggregate>
    >>
    auto as_tuple(Aggregate& aggregate) {
        constexpr int arity = arity_of<Aggregate>;
        return detail::as_tuple(aggregate, detail::value_tag<arity>{});
    }

    /// Copies the given aggregate as a tuple.

    template <class Aggregate, class = std::enable_if_t<
        is_aggregate<std::remove_reference_t<Aggregate>>
    >>
    auto to_tuple(Aggregate&& aggregate) {
        constexpr int arity = arity_of<std::remove_reference_t<Aggregate>>;
        return detail::to_tuple(std::forward<Aggregate>(aggregate), detail::value_tag<arity>{});
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

}
