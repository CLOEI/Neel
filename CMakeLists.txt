cmake_minimum_required(VERSION 3.20)
project(Neel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/enet-socks5)
add_subdirectory(lib/cpr)
add_executable(Neel main.cpp)

target_link_libraries(Neel enet cpr::cpr)