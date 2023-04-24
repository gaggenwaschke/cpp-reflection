#pragma once

#include <functional>

#include "reflection/structured_binding_member_reference.hpp"

namespace reflection
{
    template <typename member_object_reference_type, typename reflected_type>
    concept member_object_reference_for = requires(member_object_reference_type &member_object_reference, reflected_type &reflected) {
                                              std::invoke(member_object_reference, reflected);
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
            using indices = std::make_index_sequence<detail::get_reference_tuple_size<reflected_type>::value()>;

            constexpr auto member_reference_maker = []<std::size_t... indices>(std::index_sequence<indices...>)
            {
                return std::make_tuple(member_reference_by_tuple_index<reflected_type, indices>{}...);
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
