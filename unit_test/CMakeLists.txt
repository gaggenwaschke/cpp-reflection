cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(FetchContent)
fetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.3.2
)
fetchContent_MakeAvailable(Catch2)

add_executable(cpp-reflection_unit_test
    names.cpp
    member_objects.cpp)
target_link_libraries(cpp-reflection_unit_test PRIVATE
    cpp-reflection::cpp-reflection
    Catch2::Catch2WithMain)

add_executable(cpp-reflection::unit_test ALIAS cpp-reflection_unit_test)
 