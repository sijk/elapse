find_package(Qt5DBus REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qxt REQUIRED)

set(deviceproxy_SRCS
    deviceproxy.cpp
)

set(deviceproxy_HDRS
    deviceproxy.h
    dbus_interfaces.h
)

qt5_wrap_cpp(deviceproxy_SRCS ${deviceproxy_HDRS})
qt5_add_dbus_interfaces(deviceproxy_SRCS ${ELAPSE_DBUS_XML})

add_library(deviceproxy STATIC ${deviceproxy_SRCS})

target_include_directories(deviceproxy
    PUBLIC  ${ELAPSE_COMMON_INCLUDE_DIRS}
    PRIVATE ${ELAPSE_COMMON_DBUS_INCLUDE_DIRS}
)

target_link_libraries(deviceproxy
    PUBLIC  Qt5::DBus
            Qt5::Network
    PRIVATE Qxt::Core
)
