cmake_minimum_required(VERSION 3.5)
project(reviser)
aux_source_directory(. CMAKE_RESOURCES)
add_executable(reviser ${CMAKE_RESOURCES})
