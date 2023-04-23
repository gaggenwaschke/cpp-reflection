#pragma once

#include <cstddef>
#include <tuple>

#include "reflection/detail/struct_to_reference_tuple.hpp"

namespace reflection
{
    template <typename type_to_get_member_from, std::size_t index>
    struct member_reference_by_tuple_index
    {
        using class_type = std::remove_const_t<type_to_get_member_from>;
        using member_type = std::remove_cvref_t<decltype(std::get<index>(detail::object_to_reference_tuple<class_type>{}(std::declval<class_type&>())))>;

        constexpr auto &operator()(class_type &value) const
        {
            return std::get<index>(detail::object_to_reference_tuple<class_type>{}(value));
        }

        constexpr const auto &operator()(const class_type &value) const
        {
            return std::get<index>(detail::object_to_reference_tuple<const class_type>{}(value));
        }
    };
} // namespace reflection
