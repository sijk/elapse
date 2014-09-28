find_package(Qt5Widgets REQUIRED)
find_package(Qwt REQUIRED)

set(elapse_SRCS
    main.cpp
    elapseclient.cpp
    batterymonitor.cpp
    spinner.cpp
)

set(elapse_HDRS
    elapseclient.h
    batterymonitor.h
    spinner.h
)

qt5_wrap_cpp(elapse_SRCS ${elapse_HDRS})
qt5_wrap_ui(elapse_SRCS elapseclient.ui)
qt5_add_resources(elapse_SRCS ${ELAPSE_CLIENT_SOURCE_DIR}/img/images.qrc)

add_executable(elapse ${elapse_SRCS})

target_include_directories(elapse
    PRIVATE ${ELAPSE_COMMON_INCLUDE_DIRS}
)

target_link_libraries(elapse
    Qt5::Widgets
    Qwt
    deviceproxy
    pipeline
    pluginmanager
    loggerwidget
    elapseplugin
)

install(
    TARGETS elapse
    RUNTIME DESTINATION ${INSTALL_BIN_DIR}
)
