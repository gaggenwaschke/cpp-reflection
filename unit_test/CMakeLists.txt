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
    member_objects/auto_structured_binding.cpp
    member_objects/manual_with_name.cpp
    member_objects/manual_without_name.cpp)
target_include_directories(cpp-reflection_unit_test PRIVATE ./)
target_link_libraries(cpp-reflection_unit_test PRIVATE
    cpp-reflection::cpp-reflection
    Catch2::Catch2WithMain)

add_executable(cpp-reflection::unit_test ALIAS cpp-reflection_unit_test)
 