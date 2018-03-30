
#pragma once

#include <type_traits>

namespace att::detail {

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

    namespace detail {
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
    constexpr bool is_detected = detail::is_detected<void, Expr, Ts...>::value;

}
