
/// ----- Aggregates to Tuples -----
///
/// Auto-generated header which glues :
///   - tools.hpp
///   - core.hpp
///   - comparisons.hpp
///   - hash.hpp

#pragma once

#include <tuple>
#include <type_traits>
#include <functional>

/// Auto-merge of tools
namespace att::detail {

    /// Used to retrieve classes from an overload or a specialization.

    template <class T>
    struct type_tag {
        using type = T;
    };

    template <class...Ts>
    struct types_tag {};

    /// Same for constexpr values.

    template <class T, T arg>
    struct value_tag {
        static constexpr auto value = arg;
    };

    template <class T, T...args>
    struct values_tag {};

    /// Same for template classes.

    template <template <class...> class T>
    struct hightype_tag {};

    // Used to create a sequence of classes in a tag.

    namespace impl {
        template <int I, class...Ts>
        struct make_types_tag;
        template <int I, class T, class...Ts>
        struct make_types_tag<I, T, Ts...> {
            using type = typename make_types_tag<I - 1, T, T, Ts...>::type;
        };
        template <class T, class...Ts>
        struct make_types_tag<0, T, Ts...> {
            using type = types_tag<Ts...>;
        };
    }

    template <unsigned N, class T>
    using make_types_tag = typename impl::make_types_tag<N, T>::type;

    // Used to create a sequence of values in a tag.

    namespace impl {
        template <int I, class T, T...args>
        struct make_values_tag;
        template <int I, class T, T arg, T...args>
        struct make_values_tag<I, T, arg, args...> {
            using type = typename make_values_tag<I - 1, T, arg, arg, args...>::type;
        };
        template <class T, T arg, T...args>
        struct make_values_tag<0, T, arg, args...> {
            using type = values_tag<T, args...>;
        };
    }

    template <unsigned N, class T, T arg>
    using make_values_tag = typename impl::make_values_tag<N, T, arg>::type;

    /// Used to represent any class.

    struct wildcard {
        template <class T, class = std::enable_if_t<
            !std::is_lvalue_reference_v<T>
        >>
        operator T&&() const;

        template <class T, class = std::enable_if_t<
            std::is_copy_constructible_v<T>
        >>
        operator T&() const;
    };

    /// Wildcard parametred by a class so it can be folded.

    template <class = void>
    static constexpr const wildcard any{};

    /// This wildcard cannot be converted to a specific type.
    
    template <class Ex>
    struct wildcard_except {
        template <class T, class = std::enable_if_t<
            !std::is_same_v<std::decay_t<Ex>, std::decay_t<T>> && // Maybe lighten decay
            !std::is_lvalue_reference_v<T>
        >>
        operator T&&() const;

        template <class T, class = std::enable_if_t<
            !std::is_same_v<std::decay_t<Ex>, std::decay_t<T>> &&
            std::is_copy_constructible_v<T>
        >>
        operator T&() const;
    };

    /// Detect if an expression is valid with the given class template arguments.

    namespace impl {
        template <class SFINAE, template <class...> class Expr, class...Ts>
        struct is_detected {
            static constexpr bool value = false;
        };
        template <template <class...> class Expr, class...Ts>
        struct is_detected<std::void_t<Expr<Ts...>>, Expr, Ts...> {
            static constexpr bool value = true;
        };
    }

    template <template <class...> class Expr, class...Ts>
    constexpr bool is_detected = impl::is_detected<void, Expr, Ts...>::value;

}
/// Auto-merge of core
namespace att {

    /// Defines the max arity that a type can have.
    /// This size can be increased if as_tuple and to_tuple functions for a greater arity are provided.

    constexpr int max_arity = 20;

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
            if constexpr (!detail::is_brace_constructible<T, 0> ||
                detail::is_brace_constructible<T, max_arity + 1>)
            {
                return -1;
            }
            else if constexpr (detail::is_one_arg_constructible<T>) {
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
    constexpr int arity_of = impl::arity_of<T>();

    /// Helper value which indicates if a type is an aggregate.

    template <class T>
    constexpr bool is_aggregate = arity_of<T> != -1;

    namespace impl {

        /// Dispatched functions to make tuples based on the aggregate arity.

        template <class Aggregate, int Arity>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, Arity>);
        template <class Aggregate, int Arity>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, Arity>);

        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 0>) {
            return std::make_tuple();
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 0>) {
            return std::make_tuple();
        }

        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 1>) {
            auto& [v1] = aggregate;
            return std::forward_as_tuple(v1);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 1>) {
            auto&& [v1] = aggregate;
            return std::make_tuple(v1);
        }

        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 2>) {
            auto& [v1, v2] = aggregate;
            return std::forward_as_tuple(v1, v2);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 2>) {
            auto&& [v1, v2] = aggregate;
            return std::make_tuple(v1, v2);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 3>) {
            auto& [v1, v2, v3] = aggregate;
            return std::forward_as_tuple(v1, v2, v3);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 3>) {
            auto&& [v1, v2, v3] = aggregate;
            return std::make_tuple(v1, v2, v3);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 4>) {
            auto& [v1, v2, v3, v4] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 4>) {
            auto&& [v1, v2, v3, v4] = aggregate;
            return std::make_tuple(v1, v2, v3, v4);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 5>) {
            auto& [v1, v2, v3, v4, v5] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 5>) {
            auto&& [v1, v2, v3, v4, v5] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 6>) {
            auto& [v1, v2, v3, v4, v5, v6] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 6>) {
            auto&& [v1, v2, v3, v4, v5, v6] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 7>) {
            auto& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 7>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 8>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 8>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 9>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 9>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 10>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 10>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 11>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 11>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 12>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 12>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 13>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 13>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 14>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 14>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 15>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 15>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 16>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 16>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 17>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 17>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 18>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 18>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 19>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 19>) {
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
            return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
        }
        
        template <class Aggregate>
        auto as_tuple(Aggregate& aggregate, detail::value_tag<int, 20>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
        }
        template <class Aggregate>
        auto to_tuple(Aggregate&& aggregate, detail::value_tag<int, 20>) {
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
        return impl::as_tuple(aggregate, detail::value_tag<int, arity>{});
    }

    /// Copies the given aggregate as a tuple.

    template <class Aggregate, class = std::enable_if_t<
        is_aggregate<std::remove_reference_t<Aggregate>>
    >>
    auto to_tuple(Aggregate&& aggregate) {
        constexpr int arity = arity_of<std::remove_reference_t<Aggregate>>;
        return impl::to_tuple(std::forward<Aggregate>(aggregate), detail::value_tag<int, arity>{});
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
/// Auto-merge of comparisons
namespace att {

    /// Operator '=='

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

    /// Equality forward declaration.

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
                    test_equality_tuple(
                        lhs,
                        rhs,
                        detail::value_tag<int, I + 1>{});
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

    /// Operator '<'

    /// Check if inferior operator is detected for a type.

    namespace detail {
        namespace impl {
            template <class T>
            using less_expr = decltype(
                std::declval<T const&>() < std::declval<T const&>()
            );
        }
        template <class T>
        constexpr bool has_less = is_detected<impl::less_expr, T>;
    }

    /// Less forward declaration.

    namespace operators {
        template <class T, class = std::enable_if_t<
            detail::has_less<T> || is_aggregate<T>
        >>
        bool operator<(T const& lhs, T const& rhs);
    }

    /// Test less of tuples recursively.

    namespace impl {
        template <int I, class...Ts>
        bool test_less_tuple(
                std::tuple<Ts...> const& lhs,
                std::tuple<Ts...> const& rhs,
                detail::value_tag<int, I>)
        {
            if constexpr (I == sizeof...(Ts)) {
                return false;
            }
            else {
                using namespace att::operators;

                auto& lv = std::get<I>(lhs);
                auto& rv = std::get<I>(rhs);
                if (lv < rv) return true;
                if (rv < lv) return false;
                
                return  test_less_tuple(
                            lhs,
                            rhs,
                            detail::value_tag<int, I + 1>{});
            }
        }
    }

    /// Less implementation.

    namespace operators {
        template <class T, class SFINAE>
        bool operator<(T const& lhs, T const& rhs) {
            if constexpr (detail::has_less<T>) {
                return lhs < rhs;
            }
            else { // T is aggregate
                return impl::test_less_tuple(
                    as_tuple(lhs),
                    as_tuple(rhs),
                    detail::value_tag<int, 0>{});
            }
        }
    }

}
/// Auto-merge of hash
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
                std::tuple<Ts...> const& tuple,
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
