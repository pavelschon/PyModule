##
# @file CMakeLists.txt
#
# Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
#

cmake_minimum_required( VERSION 3.0 )

project( pymodule CXX )

set( CMAKE_VERBOSE_MAKEFILE OFF )

add_compile_options( -Wall )
add_compile_options( -pedantic )
add_compile_options( -fPIC )
add_compile_options( -std=c++14 )

find_package( PythonInterp REQUIRED )
find_package( PythonLibs ${PYTHON_VERSION_STRING} EXACT REQUIRED )

find_package( Boost COMPONENTS python REQUIRED )

set( Boost_FULL_VERSION ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION} )

execute_process (
    COMMAND ${PYTHON_EXECUTABLE} -c "import distutils.sysconfig as cfg; print(cfg.get_python_lib())"
    OUTPUT_VARIABLE PYTHON_PKG_PATH OUTPUT_STRIP_TRAILING_WHITESPACE
)

message( STATUS "Python libraries: ${PYTHON_LIBRARIES}" )
message( STATUS "Python include dirs: ${PYTHON_INCLUDE_DIRS}" )
message( STATUS "Python install path: ${PYTHON_PKG_PATH}")
message( STATUS "Boost libraries: ${Boost_LIBRARIES}" )
message( STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}" )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${PYTHON_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

add_library( pymodule SHARED src/PyModule.cpp )

# remove 'lib' prefix
set_target_properties( pymodule PROPERTIES PREFIX "" )
target_link_libraries( pymodule
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)

install(
    TARGETS pymodule
    DESTINATION ${PYTHON_PKG_PATH}/pymodule
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pymodule
    DESTINATION ${PYTHON_PKG_PATH}
    FILES_MATCHING PATTERN "*.py"
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/README.md
    ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
    DESTINATION /usr/share/pymodule
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

set( CPACK_GENERATOR "DEB" )

set( CPACK_PACKAGE_VERSION_MAJOR "0" )
set( CPACK_PACKAGE_VERSION_MINOR "1" )
set( CPACK_PACKAGE_VERSION_PATCH "0" )

set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "PyModule - boost::python template project" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Pavel Schön <pavel@schon.cz>" )
set( CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/pavelschon/PyModule.git")

if( "${PYTHON_VERSION_MAJOR}" STREQUAL "3" )

message( STATUS "Building package for Python 3" )
set( CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "python3-dev (>= ${PYTHON_VERSION_STRING}), libboost-all-dev, g++" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "python3 (>= ${PYTHON_VERSION_STRING}), libboost-python${Boost_FULL_VERSION}" )

else()

message( STATUS "Building package for Python 2" )
set( CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "python-dev (>= ${PYTHON_VERSION_STRING}), libboost-all-dev, g++" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "python (>= ${PYTHON_VERSION_STRING}), python (<< 2.8), libboost-python${Boost_FULL_VERSION}" )

endif()

include(CPack)

