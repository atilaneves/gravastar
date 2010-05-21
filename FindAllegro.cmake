cmake_minimum_required(VERSION 2.8)

find_path(ALLEGRO_INCLUDE_DIR allegro.h
          PATHS
          /usr/local/include
          /usr/include
          c:/allegro/include)

message("allegro.h found in ${ALLEGRO_INCLUDE_DIR}")

find_library(ALLEGRO_LIBRARY alleg
             PATHS ${ALLEGRO_INCLUDE_DIR}/../lib
	     NO_DEFAULT_PATH)


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
      set(ALLEGRO_LIBRARIES "-lalleg-4.2.2")
    endif()
endif()

message("ALLEGRO_LIBRARIES set to ${ALLEGRO_LIBRARIES}")

