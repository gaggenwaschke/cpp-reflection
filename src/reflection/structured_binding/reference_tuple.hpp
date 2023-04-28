#pragma once

#include <cstdlib>
#include <tuple>
#include <type_traits>
#include <functional>

#include "reflection/structured_binding/bind.hpp"

namespace reflection::structured_binding
{
    // This part ist stolen from here: https://www.reddit.com/r/cpp/comments/dz1sgk/comment/f85kyji/?utm_source=share&utm_medium=web3x

    template <typename T, typename... TArgs>
    auto is_aggregate_constructable_impl(std::tuple<TArgs...>) -> decltype(T{std::declval<TArgs>()...});

    template <typename T, typename TArgs, typename = void>
    struct is_aggregate_constructable : std::false_type
    {
    };

    template <typename T, typename TArgs>
    struct is_aggregate_constructable<T, TArgs, std::void_t<decltype(is_aggregate_constructable_impl<T>(std::declval<TArgs>()))>> : std::true_type
    {
    };

    // Checks if type can be initialized from braced-init-list.
    template <typename T, typename TArgs>
    constexpr auto is_aggregate_constructable_v = is_aggregate_constructable<T, TArgs>::value;

    // Class is convertible to anything.
    class any
    {
    public:
        template <typename T>
        operator T() const;
    };

    template <class T, typename... TArgs>
    constexpr size_t num_bindings_impl()
    {
        if constexpr (is_aggregate_constructable<T, std::tuple<TArgs...>>())
        {
            return num_bindings_impl<T, any, TArgs...>();
        }
        else
        {
            return sizeof...(TArgs) - 1;
        }
    };

    template <typename T>
    constexpr auto struct_bind_num_v = num_bindings_impl<T, any>();

    template <typename type_to_bind>
    constexpr auto get_reference_tuple_from_object(type_to_bind &object)
    {
        constexpr auto size{struct_bind_num_v<type_to_bind>};
        using type = type_to_bind;
        return bind_n_member_references<size, type>(object);
    }
} // namespace reflection::detail
