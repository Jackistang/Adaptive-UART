cmake_minimum_required(VERSION 3.12)

# (1) Look for installed version of CppUTest
if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

# abr_soft
add_executable(abr_soft 
    abr_soft.cpp
    ../src/abr.c)

target_include_directories(abr_soft PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/
    )

target_link_libraries(abr_soft PRIVATE CppUTest CppUTestExt)