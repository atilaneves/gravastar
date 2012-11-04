cmake_minimum_required(VERSION 2.8)

project(gravastar)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(Allegro REQUIRED)
include_directories(${ALLEGRO_INCLUDE_DIR})
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
ENDIF()


#set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: Debug Release"
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(GRAV_FLAGS_DEBUG "-Wall -g -pg -fno-inline -std=gnu++0x")
set(GRAV_FLAGS_RELEASE "-Wall -O1 -std=gnu++0x")

set(CMAKE_C_FLAGS_DEBUG ${GRAV_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_DEBUG ${GRAV_FLAGS_DEBUG})

set(CMAKE_C_FLAGS_RELEASE ${GRAV_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELEASE ${GRAV_FLAGS_RELEASE})

message("Release C   flags are ${CMAKE_C_FLAGS_RELEASE}")
message("Debug   C   flags are ${CMAKE_C_FLAGS_DEBUG}")
message("Release C++ flags are ${CMAKE_CXX_FLAGS_RELEASE}")
message("Debug   C++ flags are ${CMAKE_CXX_FLAGS_DEBUG}")
message("Build type is ${CMAKE_BUILD_TYPE}")



file(GLOB SRCS_ROOT src/*.cpp)
file(GLOB SRCS_AI src/ai/*.cpp)
file(GLOB SRCS_MP3 src/AllegroMP3/*.c)
file(GLOB SRCS_API src/AllegroAPI/*.cpp)
file(GLOB SRCS_MENU src/menu/*.cpp)
file(GLOB SRCS_POWERUPS src/powerups/*.cpp)
file(GLOB SRCS_SHIPS src/ships/*.cpp)
file(GLOB SRCS_NETWORKING src/networking/*.cpp)

set(SRCS ${SRCS_NETWORKING} ${SRCS_ROOT} ${SRCS_AI} ${SRCS_MP3} ${SRCS_API} ${SRCS_MENU}
         ${SRCS_POWERUPS} ${SRCS_SHIPS} 
         ${CMAKE_SOURCE_DIR}/src/grav.rc)


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(GRAV_BIN_DIR games)
  set(GRAV_DATA_DIR share/games/gravastar)
else()
  set(GRAV_BIN_DIR "foo/..")  #hack to keep it in the same dir
  set(GRAV_DATA_DIR "foo/..") #same
endif()


include_directories(src)
include_directories(src/ai)
include_directories(src/AllegroMP3)
include_directories(src/AllegroAPI)
include_directories(src/menu)
include_directories(src/powerups)
include_directories(src/ships)
include_directories(src/networking)

add_definitions("-DDEV_DATAFILE_DIR=\"${CMAKE_SOURCE_DIR}\"")
add_definitions("-D_WIN32_WINNT=0x0700") #boost asio
if(UNIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
  add_definitions("-DDATAFILE_DIR=\"${CMAKE_INSTALL_PREFIX}/${GRAV_DATA_DIR}\"")
else()
  add_definitions("-DDATAFILE_DIR=\"${CMAKE_INSTALL_PREFIX}\"")
endif()

if(WIN32 AND ${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
endif()

message("Installation would be to ${CMAKE_INSTALL_PREFIX}/${GRAV_BIN_DIR}")


set(GRAVRC_SRC "${CMAKE_SOURCE_DIR}/src/grav.rc")
set(GRAVRC_OBJ "${CMAKE_BINARY_DIR}/grav.rc.o")
set(WINDRES windres ${GRAVRC_SRC} ${GRAVRC_OBJ})
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_custom_command(OUTPUT ${GRAVRC_OBJ}
                     COMMAND ${WINDRES})
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_executable(gravastar ${SRCS} ${GRAVRC_OBJ})
  add_executable(client src/networking/client.cpp)
else()
  add_executable(gravastar ${SRCS})
endif()
target_link_libraries(gravastar ${ALLEGRO_LIBRARIES})
target_link_libraries(gravastar ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})
if(WIN32)
    target_link_libraries(gravastar ws2_32)
    target_link_libraries(client ws2_32)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_dependencies(gravastar gravrc)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 3)
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_EXECUTABLES gravastar;gravastar)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")
set(CPACK_PACKAGE_NAME gravastar)

if(UNIX)
  message("Setting CPACK generators for Linux/Unix")
  set(CPACK_GENERATOR "DEB;RPM")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Atila Neves <regdae@gmail.com>")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "liballegro4.2")
  set(CPACK_DEBIAN_PACKAGE_SECTION "Games")
  set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Arcade multiplayer shoot-em-up")

  set(CPACK_SOURCE_GENERATOR TGZ)
elseif(WIN32)
  message("Setting CPACK generators for Windows")
  set(CPACK_GENERATOR NSIS)
  set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/delta.ico")
endif()
include(CPack)

message("prefix is ${CMAKE_INSTALL_PREFIX}")
file(GLOB CFG cfg/*.cfg)
file(GLOB CFG_COLOURS cfg/colours/*.cfg)
file(GLOB EXPLOSIONS Explosions/*)
file(GLOB LEVELS Levels/*)
file(GLOB POWERUPS Powerups/*)
file(GLOB SHIPS Ships/*)
file(GLOB SOUNDS Sounds/*)
file(GLOB WEAPONS Weapons/*)
file(GLOB MUSIC Music/*)

install(FILES ${CFG}         DESTINATION ${GRAV_DATA_DIR}/cfg)
install(FILES ${CFG_COLOURS} DESTINATION ${GRAV_DATA_DIR}/cfg/colours)
install(FILES ${EXPLOSIONS}  DESTINATION ${GRAV_DATA_DIR}/Explosions)
install(FILES ${LEVELS}      DESTINATION ${GRAV_DATA_DIR}/Levels)
install(FILES ${POWERUPS}    DESTINATION ${GRAV_DATA_DIR}/Powerups)
install(FILES ${SHIPS}       DESTINATION ${GRAV_DATA_DIR}/Ships)
install(FILES ${SOUNDS}      DESTINATION ${GRAV_DATA_DIR}/Sounds)
install(FILES ${WEAPONS}     DESTINATION ${GRAV_DATA_DIR}/Weapons)
install(FILES ${MUSIC}       DESTINATION ${GRAV_DATA_DIR}/Music)
install(FILES fonts.dat grav.dat menu.dat stars.dat Gravastar.mp3
        DESTINATION ${GRAV_DATA_DIR})

if(UNIX)
  install(FILES src/delta.png DESTINATION "${GRAV_DATA_DIR}/../../pixmaps")
  install(FILES src/menu/gravastar DESTINATION "${GRAV_DATA_DIR}/../../menu")
  install(FILES src/gravastar.desktop DESTINATION "${GRAV_DATA_DIR}/../../applications")
  install(FILES COPYING.txt LGPL.txt README.txt DESTINATION "${GRAV_DATA_DIR}/../../doc/gravastar")
endif()

if(WIN32)
  install(FILES alleg42.dll DESTINATION ${GRAV_BIN_DIR})
endif()

install(TARGETS gravastar
        RUNTIME DESTINATION ${GRAV_BIN_DIR})
