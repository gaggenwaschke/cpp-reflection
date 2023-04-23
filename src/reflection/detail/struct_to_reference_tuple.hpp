#pragma once

#include <cstdlib>
#include <tuple>
#include <type_traits>
#include <functional>

namespace reflection::detail
{
    template <std::size_t number_elements, typename type>
    constexpr auto struct_to_reference_tuple(type &value)
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
    struct get_reference_tuple_size
    {
        using type = std::remove_cvref_t<T>;
        using result_type = std::invoke_result_t<decltype(struct_to_reference_tuple<number_elements, type>), type &>;

        constexpr static bool is_valid{!std::is_same_v<result_type, void>};

        constexpr static auto value()
        {
            static_assert(number_elements < 100, "Object can not be reflected on by structured binding!");

            if constexpr (is_valid)
            {
                return std::tuple_size_v<result_type>;
            }
            else
            {
                return get_reference_tuple_size<type, number_elements + 1>::value();
            }
        }
    };

    template <typename type_to_bind>
    struct object_to_reference_tuple
    {
        constexpr static auto size{get_reference_tuple_size<type_to_bind>::value()};

        using type = type_to_bind;
        using tuple_type = std::invoke_result_t<decltype(struct_to_reference_tuple<size, type>), type &>;

        constexpr auto operator()(type &value) const
        {
            return struct_to_reference_tuple<size, type>(value);
        }
    };
} // namespace reflection::detail
