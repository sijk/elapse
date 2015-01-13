find_package(Qt5Widgets REQUIRED)
find_package(Qxt REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)

set(pluginmanager_SRCS
    pluginmanager.cpp
    pluginhost.cpp
    staticpluginhost.cpp
    nativepluginhost.cpp
    pythonpluginhost.cpp
    native/util.cpp
    python/host.cpp
)

set(pluginmanager_HDRS
    pluginmanager.h
)

qt5_wrap_cpp(pluginmanager_SRCS ${pluginmanager_HDRS})
qt5_wrap_ui(pluginmanager_SRCS pluginmanager.ui)

add_library(pluginmanager STATIC ${pluginmanager_SRCS})

target_include_directories(pluginmanager
    PUBLIC  ${ELAPSE_CLIENT_SOURCE_DIR}/include
    PRIVATE ${PYTHON_INCLUDE_DIRS}
            ${Boost_INCLUDE_DIRS}
)

target_link_libraries(pluginmanager
    PUBLIC  Qt5::Widgets
    PRIVATE ${PYTHON_LIBRARIES}
            ${Boost_LIBRARIES}
            coreplugin
            Qxt::Core
)
