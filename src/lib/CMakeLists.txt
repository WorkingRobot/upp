cmake_minimum_required (VERSION 3.18)

## Project Definition and Options ##

project(upp_lib)


## Source Files ##

add_dir_recursive(upp_lib .)


## Define upp_lib library ##

add_library(upp_lib ${upp_lib_SOURCES})


## Dependencies ##

find_library(MBEDTLS_LIBRARY mbedtls REQUIRED)
get_filename_component(MBEDTLS_LIBRARY ${MBEDTLS_LIBRARY} DIRECTORY)
find_path(MBEDTLS_INCLUDE_DIR mbedtls/version.h REQUIRED)
target_link_libraries(upp_lib ${MBEDTLS_LIBRARY}/mbedcrypto.lib)
target_include_directories(upp_lib SYSTEM PRIVATE ${MBEDTLS_INCLUDE_DIR})


## Properties ##

# C++20 #
set_property(TARGET upp_lib PROPERTY CXX_STANDARD 20)

# Add .pdb for release builds #
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_BUILD_TYPE MATCHES "Release")
   target_compile_options(upp_lib PRIVATE /Zi)
   set_target_properties(upp_lib PROPERTIES
        LINK_FLAGS "/INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF"
        COMPILE_PDB_NAME upp_lib
        COMPILE_PDB_OUTPUT_DIR ${CMAKE_BINARY_DIR}
   )
endif()
