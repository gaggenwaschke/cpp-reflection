#include <catch2/catch_test_macros.hpp>
#include <reflection/member_objects.hpp>
#include <functional>

#include "mock.hpp"

TEST_CASE("Getting member object references by structured binding")
{
    constexpr auto member_object_references = reflection::member_objects<mock::Clown>{}();
    CHECK(std::tuple_size_v<decltype(member_object_references)> == 2);
    auto first_reference = std::get<0>(member_object_references);
    auto second_reference = std::get<1>(member_object_references);

    using first_type = decltype(first_reference);
    using first_class_type = first_type::class_type;
    using first_member_type = first_type::member_type;
    using second_type = decltype(second_reference);
    using second_class_type = second_type::class_type;
    using second_member_type = second_type::member_type;

    CHECK(std::same_as<mock::Clown, first_class_type>);
    CHECK(std::same_as<int, first_member_type>);
    CHECK(std::same_as<mock::Clown, second_class_type>);
    CHECK(std::same_as<char, second_member_type>);

    mock::Clown clown{1, 2};
    CHECK(std::invoke(first_reference, clown) == 1);
    CHECK(std::invoke(second_reference, clown) == 2);

    std::invoke(first_reference, clown) = 10;
    CHECK(clown.first == 10);
    std::invoke(second_reference, clown) = 20;
    CHECK(clown.second == 20);
}
