cmake_minimum_required(VERSION 3.12)
SET(GCC_COVERAGE_LINK_FLAGS    "-lm -lGL -lGLU -lglut")
set (CMAKE_CXX_FLAGS "-lm -lGL -lGLU -lglut")

project(Collision)

include_directories("include/")

add_executable(${PROJECT_NAME} "main.cpp" "src/vector.cpp" "src/points.cpp" "src/sphere.cpp" "src/bruteforce.cpp" "src/kdtree.cpp" "src/looseocttree.cpp" "src/octtree.cpp")