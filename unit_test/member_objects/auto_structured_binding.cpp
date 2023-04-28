#include <catch2/catch_test_macros.hpp>
#include <reflection/member_object_references.hpp>
#include <functional>

#include "mock.hpp"

TEST_CASE("Getting member object references by structured binding with two members")
{
    constexpr auto member_object_references = reflection::get_member_object_references<mock::Clown>();
    CHECK(std::tuple_size_v<decltype(member_object_references)> == 2);
    auto first_reference = std::get<0>(member_object_references);
    auto second_reference = std::get<1>(member_object_references);

    mock::Clown clown{1, 2};
    CHECK(std::invoke(first_reference, clown) == 1);
    CHECK(std::invoke(second_reference, clown) == 2);

    std::invoke(first_reference, clown) = 10;
    CHECK(clown.first == 10);
    std::invoke(second_reference, clown) = 20;
    CHECK(clown.second == 20);
}

TEST_CASE("Getting member object reference by structured binding with three members")
{
    constexpr auto member_object_references = reflection::get_member_object_references<mock::Car>();
    CHECK(std::tuple_size_v<decltype(member_object_references)> == 3);

    auto speed_reference = std::get<0>(member_object_references);
    auto fuel_reference = std::get<1>(member_object_references);
    auto passenger_reference = std::get<2>(member_object_references);

    mock::Car car{1, 2, 3};
    CHECK(std::invoke(speed_reference, car) == 1);
    CHECK(std::invoke(fuel_reference, car) == 2);
    CHECK(std::invoke(passenger_reference, car) == 3);

    std::invoke(speed_reference, car) = 10;
    CHECK(car.speed == 10);
    std::invoke(fuel_reference, car) = 20;
    CHECK(car.fuel == 20);
    std::invoke(passenger_reference, car) = 30;
    CHECK(car.passengers == 30);
}