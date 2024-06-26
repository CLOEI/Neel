cmake_minimum_required(VERSION 3.20)
project(Neel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
add_subdirectory(lib/enet-socks5)
add_subdirectory(lib/cpr)
add_subdirectory(lib/spdlog)
add_executable(Neel main.cpp packet/data.cpp connect/connect.cpp bot/bot.cpp bot/manager.cpp packet/handler.cpp utils/binarystreamreader.cpp itemdat/itemdat.cpp)

target_link_libraries(Neel enet cpr::cpr spdlog::spdlog ${OPENSSL_LIBRARIES})
FILE(COPY items.dat DESTINATION ${CMAKE_BINARY_DIR})