cmake_minimum_required(VERSION 3.13)
project(radar_tcp)

set(CMAKE_CXX_STANDARD 17)

add_executable(radar_tcp main.cpp Radar_Data.h)
find_package(Threads REQUIRED)
target_link_libraries(radar_tcp Threads::Threads)
add_executable(sync_server sync_server.cpp Radar_Data.h)
find_package(Threads REQUIRED)
target_link_libraries(sync_server Threads::Threads)