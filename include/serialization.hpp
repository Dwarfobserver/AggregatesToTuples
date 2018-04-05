
/// Defines the operators '<<' and '>>' for aggregates in the namespace att::operators.
/// They accept any class on the left side.

#pragma once

#include <loops.hpp>

namespace att {

    /// Operator '<<'

    /// The operator implementation. Put aside to avoid operator resolution making an infinite recursion.

    namespace impl {
        template <class Serializer, class T>
        using serialize_expr = decltype(
            std::declval<Serializer&>() << std::declval<T const&>()
        );
        template <class Serializer, class T>
        constexpr void serialize(Serializer& serializer, T const& data) {
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
        constexpr Serializer& operator<<(Serializer& serializer, T const& data) {
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
        constexpr void deserialize(Deserializer& deserializer, T& data) {
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
        constexpr Deserializer& operator>>(Deserializer& deserializer, T& data) {
            impl::deserialize(deserializer, data);
            return deserializer;
        }
    }

}
