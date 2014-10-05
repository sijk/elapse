find_package(Qt5Gui)
include(CMakeParseArguments)

function(add_elapse_plugin)
    set(oneArgs NAME HEADER)
    set(multiArgs SOURCES LIBRARIES)
    cmake_parse_arguments(PLUGIN "" "${oneArgs}" "${multiArgs}" ${ARGN})

    if(NOT PLUGIN_NAME)
        set(PLUGIN_NAME ${CMAKE_PROJECT_NAME})
    endif()

    add_library(${PLUGIN_NAME} MODULE ${PLUGIN_HEADER} ${PLUGIN_SOURCES})
    target_link_libraries(${PLUGIN_NAME} elapse::elements ${PLUGIN_LIBRARIES})
    set_target_properties(${PLUGIN_NAME} PROPERTIES
        AUTOMOC ON
        COMPILE_DEFINITIONS QT_PLUGIN
    )
endfunction()
