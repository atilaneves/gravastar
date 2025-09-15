cmake_minimum_required(VERSION 3.16)

project(gravastar LANGUAGES C CXX)

# after cmake_minimum_required()/project()
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)  # FindBoost module removed; use config package
endif()
if(POLICY CMP0177)
  cmake_policy(SET CMP0177 NEW)  # Normalize install() DESTINATION paths
endif()


# ---- Build type & language standards -----------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug or Release" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ---- Dependencies -----------------------------------------------------------------------------
# Allegro 4 on Arch exposes a pkg-config module named "allegro" (lib name: -lalleg)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO4 REQUIRED allegro)

# Boost (system, program_options)
find_package(Boost REQUIRED COMPONENTS system program_options)

# ---- Sources -----------------------------------------------------------------------------------

file(GLOB_RECURSE GRAV_CPP CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
file(GLOB GRAV_C CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/src/AllegroMP3/*.c"
)

set(GRAV_SRCS
  ${GRAV_CPP}
  ${GRAV_C}
  "${CMAKE_SOURCE_DIR}/src/grav.rc"  # harmless on non-Windows
)

# ---- Executable --------------------------------------------------------------------------------
add_executable(gravastar ${GRAV_SRCS})

target_include_directories(gravastar PRIVATE
  "${CMAKE_SOURCE_DIR}/src"
  "${CMAKE_SOURCE_DIR}/src/ai"
  "${CMAKE_SOURCE_DIR}/src/AllegroMP3"
  "${CMAKE_SOURCE_DIR}/src/AllegroAPI"
  "${CMAKE_SOURCE_DIR}/src/menu"
  "${CMAKE_SOURCE_DIR}/src/powerups"
  "${CMAKE_SOURCE_DIR}/src/ships"
  "${CMAKE_SOURCE_DIR}/src/networking"
  "${CMAKE_SOURCE_DIR}/src/cereal"
  ${ALLEGRO4_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

# Allegro 4 libs from pkg-config; on Arch this resolves to -lalleg plus rpath/include hints.
target_link_directories(gravastar PRIVATE ${ALLEGRO4_LIBRARY_DIRS})
target_link_libraries(gravastar PRIVATE ${ALLEGRO4_LIBRARIES})

# Boost libraries (prefer imported targets if present)
if(TARGET Boost::system AND TARGET Boost::program_options)
  target_link_libraries(gravastar PRIVATE Boost::system Boost::program_options)
else()
  target_link_libraries(gravastar PRIVATE ${Boost_LIBRARIES})
endif()

# pthread on non-Windows
if(NOT WIN32)
  find_package(Threads REQUIRED)
  target_link_libraries(gravastar PRIVATE Threads::Threads)
endif()

# ---- Compile options / defines -----------------------------------------------------------------
# Replicate original flags via target properties (prefer per-config flags)
target_compile_definitions(gravastar PRIVATE
  "DEV_DATAFILE_DIR=\"${CMAKE_SOURCE_DIR}\""
)

if(UNIX)
  set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "" FORCE)
  target_compile_definitions(gravastar PRIVATE
    "DATAFILE_DIR=\"${CMAKE_INSTALL_PREFIX}/share/games/gravastar\""
  )
else()
  target_compile_definitions(gravastar PRIVATE
    "DATAFILE_DIR=\"${CMAKE_INSTALL_PREFIX}\""
  )
endif()

target_compile_options(gravastar PRIVATE
  $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-invalid-utf8 -Wno-format-security -Wno-variadic-macros -Wno-unused-but-set-variable -Wno-format-pedantic>
  $<$<CONFIG:Debug>:-g -pg -fno-inline -fsanitize=address -fno-omit-frame-pointer>
  $<$<CONFIG:Release>:-O2>
)

target_link_options(gravastar PRIVATE
  $<$<CONFIG:Debug>:-fsanitize=address>
)

# ---- Windows resource (no-op on other platforms) ----------------------------------------------
if(WIN32)
  enable_language(RC)
  # If you truly need windres, keep the custom command; otherwise RC handles .rc.
  # set(CMAKE_RC_COMPILER windres)
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()

# ---- Install layout ----------------------------------------------------------------------------
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(GRAV_BIN_DIR  games)
  set(GRAV_DATA_DIR share/games/gravastar)
else()
  # Keep legacy behavior: drop binaries & data next to the exe on non-Linux
  set(GRAV_BIN_DIR  ".")
  set(GRAV_DATA_DIR ".")
endif()

install(TARGETS gravastar RUNTIME DESTINATION ${GRAV_BIN_DIR})

file(GLOB CFG          "${CMAKE_SOURCE_DIR}/cfg/*.cfg")
file(GLOB CFG_COLOURS  "${CMAKE_SOURCE_DIR}/cfg/colours/*.cfg")
file(GLOB EXPLOSIONS   "${CMAKE_SOURCE_DIR}/Explosions/*")
file(GLOB LEVELS       "${CMAKE_SOURCE_DIR}/Levels/*")
file(GLOB POWERUPS     "${CMAKE_SOURCE_DIR}/Powerups/*")
file(GLOB SHIPS        "${CMAKE_SOURCE_DIR}/Ships/*")
file(GLOB SOUNDS       "${CMAKE_SOURCE_DIR}/Sounds/*")
file(GLOB WEAPONS      "${CMAKE_SOURCE_DIR}/Weapons/*")
file(GLOB MUSIC        "${CMAKE_SOURCE_DIR}/Music/*")

install(FILES ${CFG}          DESTINATION ${GRAV_DATA_DIR}/cfg)
install(FILES ${CFG_COLOURS}  DESTINATION ${GRAV_DATA_DIR}/cfg/colours)
install(FILES ${EXPLOSIONS}   DESTINATION ${GRAV_DATA_DIR}/Explosions)
install(FILES ${LEVELS}       DESTINATION ${GRAV_DATA_DIR}/Levels)
install(FILES ${POWERUPS}     DESTINATION ${GRAV_DATA_DIR}/Powerups)
install(FILES ${SHIPS}        DESTINATION ${GRAV_DATA_DIR}/Ships)
install(FILES ${SOUNDS}       DESTINATION ${GRAV_DATA_DIR}/Sounds)
install(FILES ${WEAPONS}      DESTINATION ${GRAV_DATA_DIR}/Weapons)
install(FILES ${MUSIC}        DESTINATION ${GRAV_DATA_DIR}/Music)
install(FILES
  "${CMAKE_SOURCE_DIR}/fonts.dat"
  "${CMAKE_SOURCE_DIR}/grav.dat"
  "${CMAKE_SOURCE_DIR}/menu.dat"
  "${CMAKE_SOURCE_DIR}/stars.dat"
  "${CMAKE_SOURCE_DIR}/Gravastar.mp3"
  DESTINATION ${GRAV_DATA_DIR}
)

if(UNIX)
  install(FILES "${CMAKE_SOURCE_DIR}/src/delta.png"          DESTINATION "${GRAV_DATA_DIR}/../../pixmaps")
  install(FILES "${CMAKE_SOURCE_DIR}/src/menu/gravastar"     DESTINATION "${GRAV_DATA_DIR}/../../menu")
  install(FILES "${CMAKE_SOURCE_DIR}/src/gravastar.desktop"  DESTINATION "${GRAV_DATA_DIR}/../../applications")
  install(FILES "${CMAKE_SOURCE_DIR}/COPYING.txt" "${CMAKE_SOURCE_DIR}/LGPL.txt" "${CMAKE_SOURCE_DIR}/README.txt"
          DESTINATION "${GRAV_DATA_DIR}/../../doc/gravastar")
endif()

# ---- CPack (trimmed; avoid Debian-specific deps) ----------------------------------------------
include(CPack)
set(CPACK_PACKAGE_NAME "gravastar")
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 3)
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt")
set(CPACK_RESOURCE_FILE_LICENSE    "${CMAKE_SOURCE_DIR}/COPYING.txt")
set(CPACK_RESOURCE_FILE_README     "${CMAKE_SOURCE_DIR}/README.txt")

if(UNIX)
  set(CPACK_GENERATOR "TGZ") # portable; DEB/RPM meta left out to avoid distro-specific deps
elseif(WIN32)
  set(CPACK_GENERATOR "ZIP")
endif()
