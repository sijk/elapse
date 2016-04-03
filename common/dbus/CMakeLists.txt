find_package(Qt5DBus)
find_package(Qxt)

set(dbus_SRCS
    src/dbus_adaptor.cpp
)

set(dbus_HDRS
    ../include/common/hardware/device_iface.h
    ../include/common/hardware/battery_iface.h
    ../include/common/hardware/eegadc_iface.h
    ../include/common/hardware/imu_iface.h
    ../include/common/hardware/camera_iface.h
)

qt5_wrap_cpp(dbus_SRCS ${dbus_HDRS})

qt5_add_dbus_adaptor(dbus_SRCS
    xml/device.xml
    common/hardware/device_iface.h
    elapse::hardware::Device
    device_adaptor)
qt5_add_dbus_adaptor(dbus_SRCS
    xml/battery.xml
    common/hardware/battery_iface.h
    elapse::hardware::Battery
    battery_adaptor)
qt5_add_dbus_adaptor(dbus_SRCS
    xml/eegadc.xml
    common/hardware/eegadc_iface.h
    elapse::hardware::EegAdc
    eegadc_adaptor)
qt5_add_dbus_adaptor(dbus_SRCS
    xml/eegchannel.xml
    common/hardware/eegadc_iface.h
    elapse::hardware::EegChannel
    eegchannel_adaptor)
qt5_add_dbus_adaptor(dbus_SRCS
    xml/imu.xml
    common/hardware/imu_iface.h
    elapse::hardware::Imu
    imu_adaptor)

add_library(dbus STATIC ${dbus_SRCS})
target_link_libraries(dbus
    PUBLIC  Qt5::DBus
    PRIVATE Qxt::Core
)
target_include_directories(dbus
    PUBLIC  ${ELAPSE_COMMON_DBUS_INCLUDE_DIRS}
    PRIVATE ${ELAPSE_COMMON_INCLUDE_DIRS}
)
