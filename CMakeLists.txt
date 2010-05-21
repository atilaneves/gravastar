cmake_minimum_required(VERSION 2.8)

project(Gravastar)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(Allegro REQUIRED)

include_directories(${ALLEGRO_INCLUDE_DIR})

file(GLOB SRCS_ROOT src/*.cpp)
file(GLOB SRCS_AI src/ai/*.cpp)
file(GLOB SRCS_MP3 src/AllegroMP3/*.c)
file(GLOB SRCS_API src/AllegroAPI/*.cpp)
file(GLOB SRCS_MENU src/menu/*.cpp)
file(GLOB SRCS_POWERUPS src/powerups/*.cpp)
file(GLOB SRCS_SHIPS src/ships/*.cpp)

set(SRCS ${SRCS_ROOT} ${SRCS_AI} ${SRCS_MP3} ${SRCS_API} ${SRCS_MENU}
         ${SRCS_POWERUPS} ${SRCS_SHIPS} ${CMAKE_SOURCE_DIR}/src/grav.rc)


include_directories(src)
include_directories(src/ai)
include_directories(src/AllegroMP3)
include_directories(src/AllegroAPI)
include_directories(src/menu)
include_directories(src/powerups)
include_directories(src/ships)

set(GRAVRC_SRC "${CMAKE_SOURCE_DIR}/src/grav.rc")
set(GRAVRC_OBJ "${CMAKE_BINARY_DIR}/grav.rc.o")
set(WINDRES windres ${GRAVRC_SRC} ${GRAVRC_OBJ})
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_custom_command(OUTPUT ${GRAVRC_OBJ}
                     COMMAND ${WINDRES})
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_executable(Gravastar ${SRCS} ${GRAVRC_OBJ})
else()
  add_executable(Gravastar ${SRCS})
endif()
target_link_libraries(Gravastar ${ALLEGRO_LIBRARIES})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_dependencies(Gravastar gravrc)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 7)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_EXECUTABLES Gravastar;Gravastar)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")
set(CPACK_PACKAGE_NAME Gravastar)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message("Setting CPACK generators for Linux")
  set(CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER ATILA <atila.neves>)
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "liballegro4.2")
  set(CPACK_DEBIAN_PACKAGE_SECTION "Games")
  set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Arcade multiplayer shoot-em-up")
  set(CPACK_SOURCE_GENERATOR TGZ)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message("Setting CPACK generators for Windows")
  set(CPACK_GENERATOR NSIS)
  set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/delta.ico")
endif()
include(CPack)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(BIN_DIR games)
  set(DATA_DIR share/Gravastar)
else()
  set(BIN_DIR "foo/..")
  set(DATA_DIR "foo/..")
endif()


file(GLOB CFG cfg/*.cfg)
file(GLOB CFG_COLOURS cfg/colours/*.cfg)
file(GLOB EXPLOSIONS Explosions/*)
file(GLOB LEVELS Levels/*)
file(GLOB POWERUPS Powerups/*)
file(GLOB SHIPS Ships/*)
file(GLOB SOUNDS Sounds/*)
file(GLOB WEAPONS Weapons/*)

install(FILES ${CFG}         DESTINATION ${DATA_DIR}/cfg)
install(FILES ${CFG_COLOURS} DESTINATION ${DATA_DIR}/cfg/colours)
install(FILES ${EXPLOSIONS}  DESTINATION ${DATA_DIR}/Explosions)
install(FILES ${LEVELS}      DESTINATION ${DATA_DIR}/Levels)
install(FILES ${POWERUPS}    DESTINATION ${DATA_DIR}/Powerups)
install(FILES ${SHIPS}       DESTINATION ${DATA_DIR}/Ships)
install(FILES ${SOUNDS}      DESTINATION ${DATA_DIR}/Sounds)
install(FILES ${WEAPONS}     DESTINATION ${DATA_DIR}/Weapons)
install(FILES fonts.dat grav.dat menu.dat stars.dat Gravastar.mp3
        DESTINATION ${DATA_DIR})

install(TARGETS Gravastar
        RUNTIME DESTINATION ${BIN_DIR})
