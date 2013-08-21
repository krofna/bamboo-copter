# - Try to find Mysql-Connector-C++
# Once done, this will define
#
#  MYSQLCONNECTORCPP_FOUND - system has Mysql-Connector-C++ installed
#  MYSQLCONNECTORCPP_INCLUDE_DIRS - the Mysql-Connector-C++ include directories
#  MYSQLCONNECTORCPP_LIBRARIES - link these to use Mysql-Connector-C++
#
# The user may wish to set, in the CMake GUI or otherwise, this variable:
#  MYSQLCONNECTORCPP_ROOT_DIR - path to start searching for the module

# Author : Raito Bezarius. (@ChocolatAuLait_)
# TODO : Support Debug version of Linux libs.

set(MYSQLCONNECTORCPP_ROOT_DIR
        "${MYSQLCONNECTORCPP_ROOT_DIR}"
        CACHE
        PATH
        "Where to start looking for this component.")

if(WIN32)
    find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
            NAMES
            mysql_connection.h
            PATHS
            "C:\\Program Files"
            "C:\\Program Files (x86)"
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            include)

    find_library(MYSQLCONNECTORCPP_LIBRARY_DEBUG
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib/debug)

    find_library(MYSQLCONNECTORCPP_LIBRARY_RELEASE
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib/opt)

else()
    find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
            mysql_connection.h
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            include)

    find_library(MYSQLCONNECTORCPP_LIBRARY
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib64
            lib)
endif()

    mark_as_advanced(MYSQLCONNECTORCPP_INCLUDE_DIR)

if (WIN32)
    mark_as_advanced(MYSQLCONNECTORCPP_LIBRARY_RELEASE MYSQLCONNECTORCPP_LIBRARY_DEBUG)
else()
    mark_as_advanced(MYSQLCONNECTORCPP_LIBRARY)
endif()

include(FindPackageHandleStandardArgs)

if (WIN32)
    find_package_handle_standard_args(MysqlConnectorCpp
            DEFAULT_MSG
            MYSQLCONNECTORCPP_INCLUDE_DIR
            MYSQLCONNECTORCPP_LIBRARY_DEBUG 
            MYSQLCONNECTORCPP_LIBRARY_RELEASE)
else()
    find_package_handle_standard_args(MysqlConnectorCpp
            DEFAULT_MSG
            MYSQLCONNECTORCPP_INCLUDE_DIR
            MYSQLCONNECTORCPP_LIBRARY)
endif()


if(MYSQLCONNECTORCPP_FOUND)
    set(MYSQLCONNECTORCPP_INCLUDE_DIRS
            "${MYSQLCONNECTORCPP_INCLUDE_DIR}")
# Add any dependencies here
    if (WIN32)
        if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
            set(MYSQLCONNECTORCPP_LIBRARIES
                    "${MYSQLCONNECTORCPP_LIBRARY_RELEASE}")
        elseif()
            set(MYSQLCONNECTORCPP_LIBRARIES
                    "${MYSQLCONNECTORCPP_LIBRARY_DEBUG}")
        endif()
    elseif()
            set(MYSQLCONNECTORCPP_LIBRARIES
                    "${MYSQLCONNECTORCPP_LIBRARY}")
    endif()
# Add any dependencies here
    mark_as_advanced(MYSQLCONNECTORCPP_ROOT_DIR)
endif() 
