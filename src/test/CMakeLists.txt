cmake_minimum_required(VERSION 3.18)

## Project Definition and Options ##

project(upp_test)


## Source Files ##

add_dir_recursive(upp_test .)


## Define executables ##

add_executable(upp_test ${upp_test_SOURCES})


## Dependencies ##

target_link_libraries(upp_test upp_lib)


## Properties ##

# C++20 #
set_property(TARGET upp_test PROPERTY CXX_STANDARD 20)

# Add .pdb for release builds #
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_BUILD_TYPE MATCHES "Release")
   target_compile_options(upp_test PRIVATE /Zi)
   set_target_properties(upp_test PROPERTIES
        LINK_FLAGS "/INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF"
        COMPILE_PDB_NAME upp_test
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
    set_property(TARGET upp_test PROPERTY MSVC_RUNTIME_LIBRARY MultiThreadedDebug)
else()
    set_property(TARGET upp_test PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded)
endif()