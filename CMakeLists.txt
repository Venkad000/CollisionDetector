cmake_minimum_required(VERSION 3.12)

project(Collision)
include_directories("include/")
add_executable(${PROJECT_NAME} "main.cpp" "src/vector.cpp" "src/points.cpp")