cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --std=c++0x")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --std=c++0x")

set(SRC foo.cpp)
add_library(networking ${SRC})

add_executable(client client_main.cpp)
target_link_libraries(client networking)

add_executable(server server_main.cpp)
target_link_libraries(server networking)

add_executable(test test.cpp test_library.cpp)
target_link_libraries(test networking)
