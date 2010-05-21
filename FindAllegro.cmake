cmake_minimum_required(VERSION 2.8)

find_path(ALLEGRO_INCLUDE_DIR allegro.h
          PATHS
          /usr/local/include
          /usr/include
          c:/allegro/include)

find_library(ALLEGRO_LIBRARY NAMES alleg alleg42
             PATHS 
	     ${ALLEGRO_INCLUDE_DIR}/../lib
	     ${ALLEGRO_INCLUDE_DIR}/../bin
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
    endif()
endif()

