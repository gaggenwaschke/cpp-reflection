#pragma once

#include <cxxabi.h>
#include <string>
#include <string_view>
#include <concepts>

namespace reflection
{
    template <typename type_to_name>
    struct name
    {
    public:
        const std::string &operator()() const
        {
            if (!value.empty())
            {
                return value;
            }

            int status{-1};
            char *raw_string = abi::__cxa_demangle(typeid(type_to_name).name(), nullptr, 0, &status);

            switch (status)
            {
            case 0:
                value = raw_string;
                return value;
            case -1:
                throw std::runtime_error("A memory allocation failure occurred.");
            case -2:
                throw std::invalid_argument("mangled_name is not a valid name under the C++ ABI mangling rules.");
            case -3:
                throw std::invalid_argument("One of the arguments is invalid.");
            default:
                throw std::runtime_error("abi::__cxa_demangle returned unexpected code");
            }
        }

    private:
        static thread_local std::string value;
    };

    template <typename type_to_name>
    thread_local std::string name<type_to_name>::value{};
} // namespace reflection
