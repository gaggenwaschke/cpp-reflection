#include <cstddef>
#include <iostream>

void print_structured_binding(std::size_t number_elements)
{
    std::cout << "if constexpr (number_elements == " << number_elements << ")\n";
    std::cout << "\t{\n"
              << "\t\tauto& [";
    for (std::size_t index{0}; index < number_elements; ++index)
    {
        std::cout << "a" << index;
        if (index != number_elements - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "] = value;\n";
    std::cout << "\t\treturn std::make_tuple(";
    for (std::size_t index{0}; index < number_elements; ++index)
    {
        std::cout << "std::ref(a" << index << ")";
        if (index != number_elements - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "\t);\n\t}\n\t";
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument{"Unexpected number of arguments. Expected number of maximum structured bindings!"};
    }

    auto number_structured_bindings = std::stol(argv[1]);
    std::cout << "template <std::size_t number_elements>\nconstexpr auto bind_n_member_references(auto &value)\n{\n\t";

    for (std::size_t index{1}; index < number_structured_bindings; ++index)
    {
        print_structured_binding(index);
        if (index != number_structured_bindings - 1)
        {
            std::cout << "else ";
        }
    }

    std::cout << "}\n";
    return 0;
}