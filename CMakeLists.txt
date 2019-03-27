cmake_minimum_required(VERSION 3.13)
project(radar_tcp)

set(CMAKE_CXX_STANDARD 17)

add_executable(radar_tcp main.cpp)
find_package(Threads REQUIRED)
target_link_libraries(radar_tcp Threads::Threads)