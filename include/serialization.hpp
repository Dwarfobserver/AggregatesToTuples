
/// Defines the operators '<<' and '>>' for aggregates in the namespace att::operators.
/// They accept any class on the left side.

#pragma once

#include <core.hpp>
#include <loops.hpp>

namespace att {

    /// Operator '<<'

    /// Defines expressions used to pass predicates to serialization functions.

    namespace impl {
        template <class LeftType>
        struct serial_expr {
            template <class T>
            using serialize = decltype(
                std::declval<LeftType&>() << std::declval<T const&>()
            );
            template <class T>
            using deserialize = decltype(
                std::declval<LeftType&>() >> std::declval<T&>()
            );
        };
    }

    // The operator implementation. Put aside to avoid operator resolution making an infinite recursion.

    namespace impl {
        template <class Serializer, class T>
        void serialize(Serializer& serializer, T const& data) {
            for_each_recursively(
                data,
                [&] (auto&& val) { serializer << val; },
                make_predicate<serial_expr<Serializer>::template serialize>());
        }
    }

    // The public operator.

    namespace operators {
        template <class Serializer, class T>
        Serializer& operator<<(Serializer& serializer, T const& data) {
            impl::serialize(serializer, data);
            return serializer;
        }
    }

    /// Operator '>>' (basically the same thing)

    // The operator implementation. Put aside to avoid operator resolution making an infinite recursion.

    namespace impl {
        template <class Deserializer, class T>
        void deserialize(Deserializer& deserializer, T& data) {
            for_each_recursively(
                data,
                [&] (auto&& val) { deserializer >> val; }, 
                make_predicate<serial_expr<Deserializer>::template deserialize>());
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
