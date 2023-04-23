#pragma once

#include "reflection/structured_binding_member_reference.hpp"

namespace reflection
{
    // TODO: Add concept

    template <typename reflected_type>
    struct member_objects
    {
        constexpr auto operator()() const
        {
            using indizes = std::make_index_sequence<detail::get_reference_tuple_size<reflected_type>::value()>;

            constexpr auto member_reference_maker = []<std::size_t... indizes>(std::index_sequence<indizes...>)
            {
                return std::make_tuple(member_reference_by_tuple_index<reflected_type, indizes>{}...);
            };

            return member_reference_maker(indizes{});
        }
    };
} // namespace reflection
