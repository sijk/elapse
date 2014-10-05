include(${ELAPSE_ROOT_SOURCE_DIR}/cmake/ElapsePlugin.cmake)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(fooplugin)
add_subdirectory(barplugin)
add_subdirectory(bazplugin)

add_custom_target(test_plugins
    DEPENDS fooplugin barplugin bazplugin
)
