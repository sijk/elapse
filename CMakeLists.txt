project(elapse-client)
cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(ELAPSE_CXX_FLAGS "-std=c++0x")

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${ELAPSE_CXX_FLAGS} -pedantic -Wall -Wextra -Werror")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE TRUE)

set(QXT_FIND_COMPONENTS QxtCore)
find_package(Qxt REQUIRED)
if(NOT ${QXT_FOUND_QXTCORE})
    message(FATAL_ERROR "Could not find Qxt.\n"
            "Ensure you have libqxt installed and then configure "
            "CMAKE_PREFIX_PATH appropriately.")
endif()

set(INSTALL_BIN_DIR bin
    CACHE PATH "Installation directory for executables")
set(INSTALL_INC_DIR include
    CACHE PATH "Installation directory for header files")
set(INSTALL_LIB_DIR lib
    CACHE PATH "Installation directory for libraries")
set(INSTALL_DOC_DIR share/doc/elapse-client
    CACHE PATH "Installation directory for documentation")
set(INSTALL_DESKTOP_DIR share/applications
    CACHE PATH "Installation directory for desktop files")
set(INSTALL_ICON_DIR share/pixmaps
    CACHE PATH "Installation directory for icon files")

set(ELAPSE_ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ELAPSE_ROOT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${ELAPSE_ROOT_SOURCE_DIR}/include)

add_subdirectory(common)
add_subdirectory(coreplugin)
add_subdirectory(app)

include(CTest)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

set(BUILD_DOCS ON CACHE BOOL "Build the documentation")
add_subdirectory(doc)

install(
    EXPORT ElapseTargets
    NAMESPACE elapse::
    DESTINATION ${INSTALL_LIB_DIR}/cmake/Elapse
)
install(
    FILES cmake/ElapseConfig.cmake cmake/ElapsePlugin.cmake
    DESTINATION ${INSTALL_LIB_DIR}/cmake/Elapse
)
