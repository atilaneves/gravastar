cmake_minimum_required(VERSION 2.8)


find_path(ALLEGRO_INCLUDE_DIR allegro.h)
find_library(ALLEGRO_LIBRARY alleg
             PATHS ${ALLEGRO_INCLUDE_DIR}/../lib
	     NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ALLEGRO
    DEFAULT_MSG
    ALLEGRO_INCLUDE_DIR ALLEGRO_LIBRARIES)

if(ALLEGRO_FOUND)
  set(ALLEGRO_LIBRARIES ${ALLEGRO_LIBRARY})
endif()

