add_elapse_test(
    SOURCES     pluginmanager_test.cpp
                nativehost_test.cpp
                pythonhost_test.cpp
    LIBRARIES   pluginmanager
                elapseplugin
    DEPENDS     test_plugins
)
