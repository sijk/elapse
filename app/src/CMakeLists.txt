find_package(Qt5Widgets REQUIRED)
find_package(Qwt REQUIRED)
find_package(Qxt REQUIRED)

set(elapse_SRCS
    main.cpp
    elapseclient.cpp
    batterymonitor.cpp
)

set(elapse_HDRS
    elapseclient.h
    batterymonitor.h
)

qt5_wrap_cpp(elapse_SRCS ${elapse_HDRS})
qt5_wrap_ui(elapse_SRCS elapseclient.ui)
qt5_add_resources(elapse_SRCS ${ELAPSE_CLIENT_SOURCE_DIR}/resources/images.qrc)

add_executable(elapse-client ${elapse_SRCS})

target_include_directories(elapse-client
    PRIVATE ${ELAPSE_COMMON_INCLUDE_DIRS}
)

target_link_libraries(elapse-client
    Qt5::Widgets
    deviceproxy
    pipeline
    pluginmanager
    loggerwidget
    widgets
    elements
)

install(
    TARGETS elapse-client
    RUNTIME DESTINATION ${INSTALL_BIN_DIR}
)
install(
    FILES ${ELAPSE_CLIENT_SOURCE_DIR}/resources/elapse-icon.svg
    RENAME elapse-client.svg
    DESTINATION ${INSTALL_ICON_DIR}
)
install(
    FILES ${ELAPSE_CLIENT_SOURCE_DIR}/resources/elapse-client.desktop
    DESTINATION ${INSTALL_DESKTOP_DIR}
)

