cmake_minimum_required(VERSION 3.22)
project(pendulum)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(pendulum main.cpp pendulum.cpp pendulum.hpp)

target_link_libraries(pendulum sfml-graphics)