
/// ----- Arity functions -----
///
/// max_arity = 50.
/// Auto-generated file which writes functions which convert aggregates to tuples.

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
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 0>) {
            return std::make_tuple();
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 0>) {
            return std::make_tuple();
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 1>) {
            auto& [v1] = aggregate;
            return std::forward_as_tuple(v1);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 1>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1] = aggregate;
            return std::make_tuple(fwd(v1, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 2>) {
            auto& [v1, v2] = aggregate;
            return std::forward_as_tuple(v1, v2);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 2>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 3>) {
            auto& [v1, v2, v3] = aggregate;
            return std::forward_as_tuple(v1, v2, v3);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 3>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 4>) {
            auto& [v1, v2, v3, v4] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 4>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 5>) {
            auto& [v1, v2, v3, v4, v5] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 5>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 6>) {
            auto& [v1, v2, v3, v4, v5, v6] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 6>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 7>) {
            auto& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 7>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 8>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 8>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 9>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 9>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 10>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 10>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 11>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 11>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 12>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 12>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 13>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 13>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 14>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 14>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 15>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 15>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 16>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 16>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 17>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 17>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 18>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 18>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 19>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 19>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 20>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 20>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 21>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 21>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 22>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 22>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 23>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 23>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 24>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 24>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 25>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 25>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 26>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 26>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 27>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 27>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 28>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 28>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 29>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 29>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 30>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 30>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 31>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 31>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 32>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 32>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 33>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 33>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 34>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 34>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 35>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 35>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 36>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 36>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 37>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 37>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 38>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 38>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 39>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 39>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 40>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 40>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 41>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 41>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 42>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 42>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 43>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 43>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 44>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 44>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 45>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 45>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 46>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 46>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 47>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 47>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag), fwd(v47, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 48>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 48>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag), fwd(v47, tag), fwd(v48, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 49>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 49>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag), fwd(v47, tag), fwd(v48, tag), fwd(v49, tag));
        }

        template <class Aggregate>
        constexpr auto as_tuple_impl(Aggregate& aggregate, value_tag<int, 50>) {
            auto& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50] = aggregate;
            return std::forward_as_tuple(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50);
        }
        template <class Aggregate>
        constexpr auto to_tuple_impl(Aggregate&& aggregate, value_tag<int, 50>) {
            constexpr auto tag = type_tag<Aggregate>{};
            auto&& [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50] = aggregate;
            return std::make_tuple(fwd(v1, tag), fwd(v2, tag), fwd(v3, tag), fwd(v4, tag), fwd(v5, tag), fwd(v6, tag), fwd(v7, tag), fwd(v8, tag), fwd(v9, tag), fwd(v10, tag), fwd(v11, tag), fwd(v12, tag), fwd(v13, tag), fwd(v14, tag), fwd(v15, tag), fwd(v16, tag), fwd(v17, tag), fwd(v18, tag), fwd(v19, tag), fwd(v20, tag), fwd(v21, tag), fwd(v22, tag), fwd(v23, tag), fwd(v24, tag), fwd(v25, tag), fwd(v26, tag), fwd(v27, tag), fwd(v28, tag), fwd(v29, tag), fwd(v30, tag), fwd(v31, tag), fwd(v32, tag), fwd(v33, tag), fwd(v34, tag), fwd(v35, tag), fwd(v36, tag), fwd(v37, tag), fwd(v38, tag), fwd(v39, tag), fwd(v40, tag), fwd(v41, tag), fwd(v42, tag), fwd(v43, tag), fwd(v44, tag), fwd(v45, tag), fwd(v46, tag), fwd(v47, tag), fwd(v48, tag), fwd(v49, tag), fwd(v50, tag));
        }

    }
}
