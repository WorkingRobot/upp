cmake_minimum_required(VERSION 3.18)

## Project Definition and Options ##

project(upp_lib)


## Source Files ##

add_dir_recursive(upp_lib .)


## Define upp_lib library ##

add_library(upp_lib ${upp_lib_SOURCES})


## Dependencies ##

# Mbedtls (for SHA hash stuff)
find_library(MBEDTLS_LIBRARY mbedtls REQUIRED)
get_filename_component(MBEDTLS_LIBRARY ${MBEDTLS_LIBRARY} DIRECTORY)
find_path(MBEDTLS_INCLUDE_DIR mbedtls/version.h REQUIRED)
target_link_libraries(upp_lib ${MBEDTLS_LIBRARY}/mbedcrypto.lib)
target_include_directories(upp_lib SYSTEM PRIVATE ${MBEDTLS_INCLUDE_DIR})

# libdeflate (for zlib/gzip decompression)
target_link_libraries(upp_lib "${CMAKE_SOURCE_DIR}/deps/libdeflate/libdeflatestatic.lib")
target_include_directories(upp_lib SYSTEM PRIVATE "${CMAKE_SOURCE_DIR}/deps/libdeflate")

# Oodle (for oodle decompression)
target_link_libraries(upp_lib "${CMAKE_SOURCE_DIR}/deps/oodle/oo2core_win64.lib")
target_include_directories(upp_lib SYSTEM PRIVATE "${CMAKE_SOURCE_DIR}/deps/oodle")


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

# Use static CRT (the code is memcpy-heavy, avoid calling those dlls if we have to)
set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  string(REPLACE "-MD" "-MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set_property(TARGET upp_lib PROPERTY MSVC_RUNTIME_LIBRARY MultiThreadedDebug)
else()
    set_property(TARGET upp_lib PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded)
endif()