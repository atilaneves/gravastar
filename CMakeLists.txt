cmake_minimum_required(VERSION 2.8)

project(gravastar)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(Allegro REQUIRED)

file(GLOB SRCS_ROOT src/*.cpp)
file(GLOB SRCS_AI src/ai/*.cpp)
file(GLOB SRCS_MP3 src/AllegroMP3/*.c)
file(GLOB SRCS_API src/AllegroAPI/*.cpp)
file(GLOB SRCS_MENU src/menu/*.cpp)
file(GLOB SRCS_POWERUPS src/powerups/*.cpp)
file(GLOB SRCS_SHIPS src/ships/*.cpp)

set(SRCS ${SRCS_ROOT} ${SRCS_AI} ${SRCS_MP3} ${SRCS_API} ${SRCS_MENU}
         ${SRCS_POWERUPS} ${SRCS_SHIPS})


include_directories(src)
include_directories(src/ai)
include_directories(src/AllegroMP3)
include_directories(src/AllegroAPI)
include_directories(src/menu)
include_directories(src/powerups)
include_directories(src/ships)


add_executable(Gravastar ${SRCS})
target_link_libraries(Gravastar ${ALLEGRO_LIBRARIES})