cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

add_executable(cpp-reflection_structured_binding
    create_structured_bindings.cpp)
add_executable(cpp-reflection::structured_binding ALIAS cpp-reflection_structured_binding)
