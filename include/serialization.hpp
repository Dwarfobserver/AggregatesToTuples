
/// Defines the operators '<<' and '>>' for std::ostream and std::istream in the namespace att::operators.
/// They are defined to print nice and deserializable strings (with braces and commas).

#pragma once

#include <loops.hpp>
#include <iostream>

namespace att {

    /// The std::ostream '<<' operator. In 'impl_ios' to avoid namespace conflit with 'impl::is_detected' inside.

    namespace impl_ios {

        /// The expression which sees if T is serializable to an std::ostream.

        template <class OStream, class T>
        using serialize_expr = decltype(
            std::declval<OStream&>() << std::declval<T const&>()
        );

        /// The serialization, outside of the 'operators' namespace.

        template <class T>
        void serialize(std::ostream& stream, T const& data);

        template <class...Ts, size_t...Is>
        void serialize_tuple(std::ostream& stream, std::tuple<Ts...>& tuple, std::index_sequence<Is...>) {
            (((stream << " , "), (serialize(stream, std::get<Is + 1>(tuple)))), ...);
        }
        template <class...Ts>
        void serialize_tuple(std::ostream& stream, std::tuple<Ts...>& tuple) {
            if constexpr (sizeof...(Ts) == 0) {
                return;
            }
            else { // Separate the first member serialization to print commas only after him
                stream << std::get<0>(tuple);
                serialize_tuple(stream, tuple, std::make_index_sequence<sizeof...(Ts) - 1>{});
            }
        }
        
        template <class T>
        void serialize(std::ostream& stream, T const& data) {

            using expression = detail::curry<serialize_expr, std::ostream>;
            using predicate = expression_predicate<expression::template type>;
            constexpr bool is_serializable = predicate::type<T>::value;

            static_assert(is_serializable || is_aggregate<T>,
                "T must be serializable to an std::ostream, or it must be an aggregate");

            if constexpr (is_serializable) {
                stream << data;
            }
            else { // T is aggregate
                auto tuple = as_tuple(data);
                stream << "{ ";
                serialize_tuple(stream, tuple);
                stream << " }";
            }
        }

        // The recursive serialization for other streams than std::ostream. Deprecated.

        template <class OStream, class T>
        void deprecated_serialize(OStream& stream, T const& data) {

            using expression = detail::curry<serialize_expr, OStream>;
            auto tag = make_predicate<expression::template type>();

            for_each_recursively(data, tag, [&stream] (auto const& val) {
                stream << val;
            });
        }
    }

    /// The public operator.
    /// By default (when OStream != std::ostream), just recursively forward the '<<' operator.
    /// This is a deprecated feature (it will be removed in the next major version).

    namespace operators {
        template <class OStream, class T>
        OStream& operator<<(OStream& stream, T const& data) {
            if constexpr (std::is_base_of_v<std::ostream, OStream>) {
                impl_ios::serialize(stream, data);
            }
            else {
                impl_ios::deprecated_serialize(stream, data);
            }
            return stream;
        }
    }

    /// The std::istream '>>' operator. In 'impl_ios' to avoid namespace conflit with 'impl' inside.

    namespace impl_ios {

        /// The expression which sees if T is deserializable from an std::istream.

        template <class IStream, class T>
        using deserialize_expr = decltype(
            std::declval<IStream&>() >> std::declval<T&>()
        );

        /// The deserialization, outside of the 'operators' namespace.

        template <class T>
        void deserialize(std::istream& is, T& data);

        template <class...Ts, size_t...Is>
        void deserialize_tuple(std::istream& stream, std::tuple<Ts...>& tuple, std::index_sequence<Is...>) {
            char token;
            (((stream >> token),
              (deserialize(stream, std::get<Is + 1>(tuple)))
            ), ...);
        }
        template <class...Ts>
        void deserialize_tuple(std::istream& stream, std::tuple<Ts...>& tuple) {
            if constexpr (sizeof...(Ts) == 0) {
                return;
            }
            else {
                stream >> std::get<0>(tuple);
                deserialize_tuple(stream, tuple, std::make_index_sequence<sizeof...(Ts) - 1>{});
            }
        }
        
        template <class T>
        void deserialize(std::istream& stream, T& data) {

            using expression = detail::curry<deserialize_expr, std::istream>;
            using predicate = expression_predicate<expression::template type>;
            constexpr bool is_deserializable = predicate::type<T>::value;
            
            static_assert(is_deserializable || is_aggregate<T>,
                "T must be deserializable from an std::istream, or it must be an aggregate");

            if constexpr (is_deserializable) {
                stream >> data;
            }
            else { // T is aggregate
                auto tuple = as_tuple(data);
                char token;
                stream >> token;
                deserialize_tuple(stream, tuple);
                stream >> token;
            }
        }
        
        // The recursive deserialization for other streams than std::istream. Deprecated.

        template <class IStream, class T>
        void deprecated_deserialize(IStream& stream, T& data) {

            using expression = detail::curry<deserialize_expr, IStream>;
            auto tag = make_predicate<expression::template type>();

            for_each_recursively(data, tag, [&stream] (auto& val) {
                stream >> val;
            });
        }
    }

    /// The public operator.
    /// By default (when IStream != std::istream), just recursively forward the '>>' operator.
    /// This is a deprecated feature (it will be removed in the next major version).

    namespace operators {
        template <class IStream, class T>
        IStream& operator>>(IStream& stream, T& data) {
            if constexpr (std::is_base_of_v<std::istream, IStream>) {
                impl_ios::deserialize(stream, data);
            }
            else {
                impl_ios::deprecated_deserialize(stream, data);
            }
            return stream;
        }
    }

}
