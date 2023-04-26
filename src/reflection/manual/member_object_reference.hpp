#pragma once

#include <type_traits>
#include <string_view>

namespace reflection::manual
{
    template <typename callable_type>
    class member_object_reference
    {
    public:
        constexpr member_object_reference(callable_type callable, std::string_view member_name) : callable{callable}, member_name{member_name}
        {
        }

        template <typename type_to_reflect>
        constexpr decltype(auto) operator()(type_to_reflect &object) const
        {
            return std::invoke(callable, object);
        }

        constexpr std::string_view name() const
        {
            return member_name;
        }

    private:
        callable_type callable;
        std::string_view member_name;
    };
} // namespace reflection::by_pointer
