
/// ----- Aggregates to Tuples -----
///
/// Auto-generated header which glues :
///   - tools.hpp
///   - arity_functions.inl
///   - core.hpp
///   - loops.hpp
///   - comparisons.hpp
///   - hash.hpp
///   - serialization.hpp

#pragma once

#include <tuple>
#include <type_traits>
#include <functional>

/// Auto-merge of tools.hpp
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

    /// Same for template types.
    
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

    /// Partially apply template type arguments to a template class.
    /// MSVC do not support argument packs here the way I tried.

    template <template <class, class> class T, class Arg>
    struct curry {
        template <class Other>
        using type = T<Arg, Other>;
    };

}
/// Auto-merge of arity_functions.inl
namespace att {

    /// Defines the max arity (the number of member variables) that an aggregate can have.
    constexpr int max_arity = 50;

    namespace detail {

        /// Forward the reference depending on the 'Aggregate' type.

        template <class Aggregate, class T>
        auto fwd(T&& val, type_tag<Aggregate>) {
            if constexpr (std::is_reference_v<Aggregate>) {
                return val;
            }
            else {
                return std::move(val);
            }
        }

        /// as_tuple and to_tuple implementation for each arity supported.

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 0>) {
            return std::make_tuple();
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 0>) {
            return std::make_tuple();
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 1>) {
            auto& [v1] = aggregate;
            return std::forward_as_tuple(v1);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 1>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1] = aggregate;
            return std::make_tuple(fwd(v1, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 2>) {
            auto& [v1, v2] = aggregate;
            return std::forward_as_tuple(v1, v2);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 2>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 3>) {
            auto& [v1, v2, v3] = aggregate;
            return std::forward_as_tuple(v1, v2, v3);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 3>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 4>) {
            auto& [v1, v2, v3, v4] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 4>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 5>) {
            auto& [v1, v2, v3, v4, v5] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 5>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 6>) {
            auto& [v1, v2, v3, v4, v5, v6] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 6>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 7>) {
            auto& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 7>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 8>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 8>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 9>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 9>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 10>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 10>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 11>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 11>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 12>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 12>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 13>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 13>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 14>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 14>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 15>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 15>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 16>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 16>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 17>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 17>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 18>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 18>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 19>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 19>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 20>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 20>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 21>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 21>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 22>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 22>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 23>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 23>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 24>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 24>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 25>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 25>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 26>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 26>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 27>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 27>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 28>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 28>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 29>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 29>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 30>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 30>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 31>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 31>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 32>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 32>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 33>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 33>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 34>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 34>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 35>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 35>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 36>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 36>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 37>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 37>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 38>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 38>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 39>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 39>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 40>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 40>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 41>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 41>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 42>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 42>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 43>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 43>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 44>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 44>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 45>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 45>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 46>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 46>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 47>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 47>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag), fwd(v47, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 48>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 48>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag), fwd(v47, tag), fwd(v48, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 49>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 49>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag), fwd(v47, tag), fwd(v48, tag), fwd(v49, tag));
        }

        template <class Aggregate>
        auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 50>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50);
        }
        template <class Aggregate>
        auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 50>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag), fwd(v47, tag), fwd(v48, tag), fwd(v49, tag), fwd(v50, tag));
        }

    }
}
/// Auto-merge of core.hpp
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
    auto as_tuple(Aggregate& aggregate) noexcept {
        constexpr int arity = arity_of<Aggregate>;
        return detail::as_tuple_impl(aggregate, detail::value_tag<int, arity>{});
    }

    /// Copies the given aggregate as a tuple.

    template <class Aggregate, class = std::enable_if_t<
        is_aggregate<std::remove_reference_t<Aggregate>>
    >>
    auto to_tuple(Aggregate&& aggregate)
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

}
/// Auto-merge of loops.hpp
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
    void for_each_recursively(T& data, predicate_tag<Predicate> predicate, F&& f) {
        
        static_assert(Predicate<T>::value || is_aggregate<T>,
            "T must be an aggregate, or the predicate for T must be true");

        if constexpr (Predicate<T>::value) {
            f(data);
        }
        else { // T is aggregate
            for_each(data, [&f, predicate] (auto&& arg) {
                for_each_recursively(arg, predicate, f);
            });
        }
    }

}
/// Auto-merge of comparisons.hpp
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

    /// Test equality implementation.

    namespace impl {
        
        template <class T>
        bool test_equality(T const& lhs, T const& rhs);

        template <class...Ts, size_t...Is>
        bool test_equality_tuple(
                std::tuple<Ts...> const& lhs,
                std::tuple<Ts...> const& rhs,
                std::index_sequence<Is...>)
        {
            return (... && test_equality(std::get<Is>(lhs), std::get<Is>(rhs)));
        }
        
        template <class T>
        bool test_equality(T const& lhs, T const& rhs) {
            
            static_assert(detail::has_equality<T> || is_aggregate<T>,
                "T must be an aggregate, or operator==(T const&, T const&) must be implemented");

            if constexpr (detail::has_equality<T>) {
                return lhs == rhs;
            }
            else { // T is aggregate
                return test_equality_tuple(
                    att::as_tuple(lhs),
                    att::as_tuple(rhs),
                    std::make_index_sequence<att::arity_of<T>>{});
            }
        }
    }

    /// Public operators.

    namespace operators {
        template <class T>
        bool operator==(T const& lhs, T const& rhs) {
            return impl::test_equality(lhs, rhs);
        }
        template <class T>
        bool operator!=(T const& lhs, T const& rhs) {
            return !impl::test_equality(lhs, rhs);
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

    /// Test less of tuples recursively.

    namespace impl {
        
        template <class T>
        bool test_less(T const& lhs, T const& rhs);

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
                auto& lv = std::get<I>(lhs);
                auto& rv = std::get<I>(rhs);
                if (test_less(lv, rv)) return true;
                if (test_less(rv, lv)) return false;
                
                return test_less_tuple(lhs, rhs, detail::value_tag<int, I + 1>{});
            }
        }
        
        template <class T>
        bool test_less(T const& lhs, T const& rhs) {

            static_assert(detail::has_less<T> || is_aggregate<T>,
                "T must be an aggregate, or operator<(T const&, T const&) must be implemented");

            if constexpr (detail::has_less<T>) {
                return lhs < rhs;
            }
            else { // T is aggregate
                return test_less_tuple(
                    as_tuple(lhs),
                    as_tuple(rhs),
                    detail::value_tag<int, 0>{});
            }
        }
    }

    /// The public operators.

    namespace operators {
        template <class T>
        bool operator<(T const& lhs, T const& rhs) {
            return impl::test_less(lhs, rhs);
        }
        template <class T>
        bool operator<=(T const& lhs, T const& rhs) {
            return !impl::test_less(rhs, lhs);
        }
        template <class T>
        bool operator>(T const& lhs, T const& rhs) {
            return impl::test_less(rhs, lhs);
        }
        template <class T>
        bool operator>=(T const& lhs, T const& rhs) {
            return !impl::test_less(lhs, rhs);
        }
    }

}
/// Auto-merge of hash.hpp
namespace att {

    /// The default function used to combine hashes.

    using hash_combiner_t = size_t (*) (size_t, size_t);

    size_t default_hash_combiner(size_t seed, size_t hash) {
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
    size_t hash(T const& data, hash_combiner_t combiner = default_hash_combiner) {
        constexpr auto tag = make_predicate<impl::hash_expr>();
        size_t seed = 0;
        for_each_recursively(data, tag, [&] (auto const& val)
        {
            using ValueT = typename std::remove_cv_t<std::remove_reference_t<decltype(val)>>;
            seed = combiner(seed, std::hash<ValueT>{}(val));
        });
        return seed;
    }

}
/// Auto-merge of serialization.hpp
namespace att {

    /// Operator '<<'

    /// The operator implementation. Put aside to avoid operator resolution making an infinite recursion.

    namespace impl {
        template <class Serializer, class T>
        using serialize_expr = decltype(
            std::declval<Serializer&>() << std::declval<T const&>()
        );
        template <class Serializer, class T>
        void serialize(Serializer& serializer, T const& data) {
            using Expression = detail::curry<serialize_expr, Serializer>;
            constexpr auto tag = make_predicate<Expression::template type>();
            
            for_each_recursively(data, tag, [&] (auto const& val) {
                serializer << val;
            });
        }
    }

    /// The public operator.

    namespace operators {
        template <class Serializer, class T>
        Serializer& operator<<(Serializer& serializer, T const& data) {
            impl::serialize(serializer, data);
            return serializer;
        }
    }

    /// Operator '>>' (basically the same thing)

    /// The operator implementation. Put aside to avoid operator resolution making an infinite recursion.

    namespace impl {
        template <class Deserializer, class T>
        using deserialize_expr = decltype(
            std::declval<Deserializer&>() >> std::declval<T&>()
        );
        template <class Deserializer, class T>
        void deserialize(Deserializer& deserializer, T& data) {
            using Expression = detail::curry<deserialize_expr, Deserializer>;
            constexpr auto tag = make_predicate<Expression::template type>();

            for_each_recursively(data, tag, [&] (auto& val) {
                deserializer >> val;
            });
        }
    }

    // The public operator.

    namespace operators {
        template <class Deserializer, class T>
        Deserializer& operator>>(Deserializer& deserializer, T& data) {
            impl::deserialize(deserializer, data);
            return deserializer;
        }
    }

}
