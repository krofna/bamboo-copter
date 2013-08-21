cmake_minimum_required(VERSION 2.8)

project(bamboo-copter)

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
    add_definitions(-Wvariadic-macros)
    set(CMAKE_CXX_FLAGS "-lpthread" ${CMAKE_CXX_FLAGS})
elseif (MSVC)

    if (MSVC_VERSION LESS 1700)

    	message(FATAL_ERROR "The project requires C++11 features. "
          "You need at least Visual Studio 11 (Microsoft Visual Studio 2012), "
          "with Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012).") 

    elseif (MSVC_VERSION EQUAL 1700)

     	message( "VC11: use Microsoft Visual Studio 2012 "
          "with Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)" ) 
    	set(CMAKE_GENERATOR_TOOLSET "v120_CTP_Nov2012" CACHE STRING "Platform Toolset" FORCE) 

    else()
    endif()

    SET(Boost_USE_STATIC_LIBS   ON)
    set(Boost_USE_MULTITHREADED ON)
    add_definitions(-D_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH)
    add_definitions(-D BOOST_THREAD_NO_LIB)
    
    macro(get_WIN32_WINNT version)
        if (WIN32 AND CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REPLACE "." "" ver ${ver})
            string(REGEX REPLACE "([0-9])" "0\\1" ver ${ver})

            set(${version} "0x${ver}")
        endif()
    endmacro()

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
else ()
    message( FATAL_ERROR "Unsupported compiler. Feel free to provide a patch :)" )
endif ()

add_subdirectory(Server)
add_subdirectory(Client)
add_subdirectory(Editor)
