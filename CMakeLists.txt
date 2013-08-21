cmake_minimum_required(VERSION 2.8)

project(bamboo-copter CXX)

set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set (CMAKE_DISABLE_SOURCE_CHANGES ON)

if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo
        MinSizeRel." FORCE )
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++11)
    add_definitions(-Wall)
    add_definitions(-Werror)
elseif (MSVC11)
    SET(Boost_USE_STATIC_LIBS   ON)
else ()
    message( FATAL_ERROR "Unsupported compiler. Feel free to provide a patch :)" )
endif ()

add_subdirectory(Server)
add_subdirectory(Client)
add_subdirectory(Editor)
