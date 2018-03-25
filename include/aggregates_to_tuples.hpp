
#pragma once

#include <type_traits>
#include <tuple>

namespace traits {

    /// Used to retrieve classes from an overload or a specialization.

    template <class T>
    struct type_tag {
        using type = T;
    };

    template <class...Ts>
    struct types_tag {};

    /// Same for constexpr values.

    template <auto arg>
    struct value_tag {
        static constexpr auto value = arg;
    };

    template <auto...args>
    struct values_tag {};

    // Used to create a sequence of classes in a tag.

    namespace detail {
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
    using make_types_tag = typename detail::make_types_tag<N, T>::type;

    // Used to create a sequence of values in a tag.

    namespace detail {
        template <int I, auto...args>
        struct make_values_tag;
        template <int I, auto arg, auto...args>
        struct make_values_tag<I, arg, args...> {
            using type = typename make_values_tag<I - 1, arg, arg, args...>::type;
        };
        template <auto arg, auto...args>
        struct make_values_tag<0, arg, args...> {
            using type = values_tag<args...>;
        };
    }

    template <unsigned N, auto arg>
    using make_values_tag = typename detail::make_values_tag<N, arg>::type;

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

}


namespace traits {

    /// Defines the max arity that a type can have.

    constexpr int max_arity = 20;

    /// Detects if a type is brace-constructible from N elements.

    namespace detail {
        template <class SFINAE, class T, class...Args>
        struct is_brace_constructible {
            static constexpr bool value = false;
        };

        template <class T, class...Args>
        struct is_brace_constructible<std::void_t<
            decltype(T{ any<Args>... })
        >, T, types_tag<Args...>> {
            static constexpr bool value = true;
        };
    }

    template <class T, unsigned N>
    constexpr bool is_brace_constructible =
        detail::is_brace_constructible<void, T, make_types_tag<N, void>>::value;

    /// Gives the arity of a type (the number of elements which construct him).
    /// If he isn't an aggregate type, returns -1.
    /// If the maximum arity is reached, stops the compilation.

    namespace detail {
        template <class T, unsigned I>
        constexpr int arity_of_rec() {
            static_assert(I < max_arity, "");
            if constexpr (!::traits::is_brace_constructible<T, I + 1>) {
                return I;
            }
            else {
                return arity_of_rec<T, I + 1>();
            }
        }

        template <class T>
        constexpr int arity_of() {
            // MSVC do not implement std::is_aggregate<T>
            if constexpr (!std::is_aggregate_v<T>) {
                return -1;
            }
            else {
                return arity_of_rec<T, 0>();
            }
        }
    }

    template <class T>
    constexpr int arity_of = detail::arity_of<T>();

}

namespace detail {

    /// Dispatched functions to make tuples based on the aggregate arity.

    template <class Aggregate, int Arity>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<Arity>);
    template <class Aggregate, int Arity>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<Arity>);

    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<0>) {
        return std::make_tuple();
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<0>) {
        return std::make_tuple();
    }

    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<1>) {
        auto& [v1] = aggregate;
        return std::forward_as_tuple(v1);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<1>) {
        auto&& [v1] = aggregate;
        return std::make_tuple(v1);
    }

    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<2>) {
        auto& [v1, v2] = aggregate;
        return std::forward_as_tuple(v1, v2);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<2>) {
        auto&& [v1, v2] = aggregate;
        return std::make_tuple(v1, v2);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<3>) {
        auto& [v1, v2, v3] = aggregate;
        return std::forward_as_tuple(v1, v2, v3);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<3>) {
        auto&& [v1, v2, v3] = aggregate;
        return std::make_tuple(v1, v2, v3);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<4>) {
        auto& [v1, v2, v3, v4] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<4>) {
        auto&& [v1, v2, v3, v4] = aggregate;
        return std::make_tuple(v1, v2, v3, v4);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<5>) {
        auto& [v1, v2, v3, v4, v5] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<5>) {
        auto&& [v1, v2, v3, v4, v5] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<6>) {
        auto& [v1, v2, v3, v4, v5, v6] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<6>) {
        auto&& [v1, v2, v3, v4, v5, v6] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<7>) {
        auto& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<7>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<8>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<8>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<9>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<9>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<10>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<10>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<11>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<11>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<12>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<12>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<13>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<13>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<14>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<14>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<15>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<15>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<16>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<16>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<17>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<17>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<18>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<18>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<19>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<19>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
    }
    
    template <class Aggregate>
    auto as_tuple(Aggregate& aggregate, traits::value_tag<20>) {
        auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
        return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
    }
    template <class Aggregate>
    auto to_tuple(Aggregate&& aggregate, traits::value_tag<20>) {
        auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
        return std::make_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
    }
}

/// as_tuple makes a tuple of references on the given aggregate.

template <class Aggregate, class = std::enable_if_t<
    std::is_aggregate_v<Aggregate>
>>
auto as_tuple(Aggregate& aggregate) {
    constexpr int arity = traits::arity_of<Aggregate>;
    return detail::as_tuple(aggregate, traits::value_tag<arity>{});
}

/// to_tuple copy the given aggregate as a tuple.

template <class Aggregate, class = std::enable_if_t<
    std::is_aggregate_v<std::remove_reference_t<Aggregate>>
>>
auto to_tuple(Aggregate&& aggregate) {
    constexpr int arity = traits::arity_of<std::remove_reference_t<Aggregate>>;
    return detail::to_tuple(std::forward<Aggregate>(aggregate), traits::value_tag<arity>{});
}

template <class Aggregate>
using tuple_type_of = typename std::remove_reference_t<decltype(
    to_tuple(std::declval<Aggregate>())
)>;
template <class Aggregate>
using tuple_ref_type_of = typename std::remove_reference_t<decltype(
    as_tuple(std::declval<Aggregate&>())
)>;
