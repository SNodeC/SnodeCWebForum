cmake_minimum_required(VERSION 3.5)

project(GetAndPostServerTemplate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
        snodec COMPONENTS express net-in core-legacy
)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE snodec::express snodec::net-in snodec::core-legacy)