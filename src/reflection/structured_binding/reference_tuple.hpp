#pragma once

#include <cstdlib>
#include <tuple>
#include <type_traits>
#include <functional>

namespace reflection::structured_binding
{
    template <std::size_t number_elements, typename type>
    constexpr auto bind_n_member_references(type &value)
    {
        if constexpr (number_elements == 2)
        {
            auto &[a, b] = value;
            return std::make_tuple(std::ref(a), std::ref(b));
        }
        else if constexpr (number_elements == 3)
        {
            auto &[a, b, c] = value;
            return std::make_tuple(std::ref(a), std::ref(b), std::ref(c));
        }
        static_assert(number_elements <= 3, "Count not implemented!");
    }

    template <typename T, std::size_t number_elements = 2>
    constexpr auto get_reference_tuple_size()
    {
        using type = std::remove_cvref_t<T>;
        using result_type = std::invoke_result_t<decltype(bind_n_member_references<number_elements, type>), type &>;

        constexpr bool is_valid{!std::is_same_v<result_type, void>};

        static_assert(number_elements < 100, "Object can not be reflected on by structured binding!");

        if constexpr (is_valid)
        {
            return std::tuple_size_v<result_type>;
        }
        else
        {
            return get_reference_tuple_size<type, number_elements + 1>();
        }
    }

    template <typename type_to_bind>
    constexpr auto get_reference_tuple_from_object(type_to_bind &object)
    {
        constexpr auto size{get_reference_tuple_size<type_to_bind>()};

        using type = type_to_bind;
        using tuple_type = std::invoke_result_t<decltype(bind_n_member_references<size, type>), type &>;

        return bind_n_member_references<size, type>(object);
    }
} // namespace reflection::detail
