#pragma once

#include <cstddef>
#include <tuple>

#include "reflection/structured_binding/reference_tuple.hpp"

namespace reflection::structured_binding
{
    template <typename type_to_get_member_from, std::size_t index>
    struct member_reference_by_tuple_index
    {
        using class_type = std::remove_const_t<type_to_get_member_from>;
        using member_type = std::remove_cvref_t<decltype(std::get<index>(structured_binding::get_reference_tuple_from_object<class_type>(std::declval<class_type &>())))>;

        constexpr auto &operator()(class_type &value) const
        {
            return std::get<index>(structured_binding::get_reference_tuple_from_object<class_type>(value));
        }

        constexpr const auto &operator()(const class_type &value) const
        {
            return std::get<index>(structured_binding::get_reference_tuple_from_object<const class_type>(value));
        }
    };
} // namespace reflection
