cmake_minimum_required(VERSION 2.8.0)
project (ilqr_cmake_list)

file(GLOB_RECURSE Foo_SOURCES "src/*.c")

include_directories(include)
add_executable (run_iLQR src/ilqr_planner_main.cpp ${Foo_SOURCES})
