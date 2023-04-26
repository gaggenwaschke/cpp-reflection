cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

add_library(cpp-reflection_cpp-reflection INTERFACE)
target_compile_features(cpp-reflection_cpp-reflection INTERFACE cxx_std_20)
target_include_directories(cpp-reflection_cpp-reflection
    INTERFACE
    ./)
    
add_library(cpp-reflection::cpp-reflection ALIAS cpp-reflection_cpp-reflection)