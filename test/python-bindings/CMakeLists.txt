add_custom_target(copy_py_test_plugin
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/plugin
            ${CMAKE_CURRENT_BINARY_DIR}/plugins/pytestplugin
)

add_elapse_test(
    SOURCES     runner.cpp
    LIBRARIES   pluginmanager
                elapseplugin
    DEPENDS     copy_py_test_plugin
)
