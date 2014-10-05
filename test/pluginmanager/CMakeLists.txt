add_elapse_test(
    SOURCES     pluginmanager_test.cpp
                nativehost_test.cpp
                pythonhost_test.cpp
    LIBRARIES   pluginmanager
                elements
    DEPENDS     test_plugins
)
