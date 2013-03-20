cmake_minimum_required(VERSION 2.8)

find_path(ALLEGRO_INCLUDE_DIR allegro.h
          PATHS
          /usr/local/include
          /usr/include
          c:/allegro/include)

message("allegro.h found in ${ALLEGRO_INCLUDE_DIR}")

find_library(ALLEGRO_LIBRARY alleg
             HINTS
             "${ALLEGRO_INCLUDE_DIR}/../lib"
             PATHS
             "/usr/lib/x86_64-linux-gnu"
             "/usr/lib"
             "${ALLEGRO_INCLUDE_DIR}/../lib/x86_64-linux-gnu"
             )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ALLEGRO
    DEFAULT_MSG
    ALLEGRO_INCLUDE_DIR ALLEGRO_LIBRARIES)

if(ALLEGRO_FOUND)
  set(ALLEGRO_LIBRARIES ${ALLEGRO_LIBRARY})
else()
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
      set(ALLEGRO_LIBRARIES "c:/allegro/bin/alleg42.dll")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
      set(ALLEGRO_LIBRARIES "-lalleg -L/usr/lib/x86_64-linux-gnu")
    endif()
endif()

message("ALLEGRO_LIBRARIES set to ${ALLEGRO_LIBRARIES}")

