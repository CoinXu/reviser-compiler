cmake_minimum_required(VERSION 3.5)
# 使用c++11
add_compile_options(-std=c++11)

project(reviser)
aux_source_directory(. CMAKE_RESOURCES)
add_executable(reviser ${CMAKE_RESOURCES})
