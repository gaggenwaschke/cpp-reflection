#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <reflection/names.hpp>

namespace mock
{
    struct Clown
    {
    };

    template <typename T>
    struct Tent
    {
    };
} // namespace mock

TEST_CASE("Names of integrals get resolved")
{
    CHECK(reflection::name<unsigned char>{}() == "unsigned char");
    CHECK(reflection::name<unsigned short>{}() == "unsigned short");
    CHECK(reflection::name<unsigned int>{}() == "unsigned int");
    CHECK(reflection::name<unsigned long>{}() == "unsigned long");
    CHECK(reflection::name<unsigned long long>{}() == "unsigned long long");

    CHECK(reflection::name<signed char>{}() == "signed char");
    CHECK(reflection::name<short>{}() == "short");
    CHECK(reflection::name<int>{}() == "int");
    CHECK(reflection::name<long>{}() == "long");
    CHECK(reflection::name<long long>{}() == "long long");
}

TEST_CASE("Custom types get resolved")
{
    CHECK(reflection::name<mock::Clown>{}() == "mock::Clown");
    CHECK(reflection::name<mock::Tent<int>>{}() == "mock::Tent<int>");
    CHECK(reflection::name<mock::Tent<mock::Clown>>{}() == "mock::Tent<mock::Clown>");
}
