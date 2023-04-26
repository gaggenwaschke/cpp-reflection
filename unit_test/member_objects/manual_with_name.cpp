#include <catch2/catch_test_macros.hpp>
#include <reflection/member_object_references.hpp>

#include "mock.hpp"

namespace reflection
{
    template <>
    struct member_object_reference_list<mock::Clown>
    {
        constexpr static auto value = std::make_tuple(
            reflection::manual::member_object_reference{&mock::Clown::first, "first"},
            reflection::manual::member_object_reference{&mock::Clown::second, "second"});
    };
} // namespace reflection

TEST_CASE("Manual member object references with name")
{
    constexpr auto member_object_references = reflection::get_named_member_object_references<mock::Clown>();
    CHECK(std::tuple_size_v<decltype(member_object_references)> == 2);
    constexpr auto first_reference = std::get<0>(member_object_references);
    constexpr auto second_reference = std::get<1>(member_object_references);

    CHECK(first_reference.name() == "first");
    CHECK(second_reference.name() == "second");

    mock::Clown clown{1, 2};
    CHECK(std::invoke(first_reference, clown) == 1);
    CHECK(std::invoke(second_reference, clown) == 2);

    std::invoke(first_reference, clown) = 10;
    CHECK(clown.first == 10);
    std::invoke(second_reference, clown) = 20;
    CHECK(clown.second == 20);
}
