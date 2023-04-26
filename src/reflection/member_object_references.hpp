#pragma once

#include <functional>
#include <ranges>
#include <concepts>

#include "reflection/structured_binding/member_reference.hpp"

namespace reflection
{
    template <typename string_like_type>
    concept string_like = std::ranges::input_range<string_like_type> && std::convertible_to<std::ranges::range_value_t<string_like_type>, char>;

    template <typename member_object_reference_type, typename reflected_type>
    concept member_object_reference_for = requires(member_object_reference_type &member_object_reference, reflected_type &reflected) {
                                              std::invoke(member_object_reference, reflected);
                                          };

    template <typename member_object_reference_type, typename reflected_type>
    concept named_member_object_reference_for = member_object_reference_for<member_object_reference_type, reflected_type> && requires {
                                                                                                                                 {
                                                                                                                                     member_object_reference_type::name
                                                                                                                                     } -> string_like;
                                                                                                                             };

    /**
     * @brief SFINAE customization point for listing member object references.
     *
     * @note Use through get_member_object_reference() function, not directly.
     */
    template <typename reflected_type>
    struct member_object_reference_list
    {
        constexpr auto operator()() const
        {
            using indices = std::make_index_sequence<structured_binding::get_reference_tuple_size<reflected_type>()>;

            constexpr auto member_reference_maker = []<std::size_t... indices>(std::index_sequence<indices...>)
            {
                return std::make_tuple(structured_binding::member_reference_by_tuple_index<reflected_type, indices>{}...);
            };

            return member_reference_maker(indices{});
        }
    };

    /**
     * @brief Get the tuple of member object references for the reflected type.
     */
    template <typename reflected_type>
    constexpr auto get_member_object_references()
    {
        constexpr auto list = member_object_reference_list<reflected_type>{}();
        std::apply([]<typename... member_object_reference_type>(const member_object_reference_type &...)
                   { static_assert((member_object_reference_for<member_object_reference_type, reflected_type> && ...), "Invalid member object reference!"); },
                   list);
        return list;
    }
} // namespace reflection
