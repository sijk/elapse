find_package(Qt5Gui REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(Eigen3 REQUIRED)

set(elapseplugin_SRCS
    offlinedatasource.cpp
    featurextractor.cpp
    classifier.cpp
    datasink.cpp
)

set(elapseplugin_HDRS
    configproxies.h
    ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse/datatypes.h
    ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse/elements/datasource.h
    ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse/elements/decoder.h
    ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse/elements/featurextractor.h
    ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse/elements/classifier.h
    ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse/elements/outputaction.h
    ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse/elements/datasink.h
    ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse/elements/simple/eegfeaturextractor.h
)

qt5_wrap_cpp(elapseplugin_SRCS ${elapseplugin_HDRS})

add_library(elapseplugin SHARED ${elapseplugin_SRCS})

target_include_directories(elapseplugin
    PUBLIC  ${EIGEN3_INCLUDE_DIR}
            ${QXT_INCLUDE_DIRS}
    PRIVATE ${ELAPSE_COMMON_INCLUDE_DIRS}
)

target_link_libraries(elapseplugin
    PUBLIC  Qt5::Gui
    PRIVATE dbus
)

target_compile_options(elapseplugin
    INTERFACE ${ELAPSE_CXX_FLAGS}
)

install(
    TARGETS elapseplugin
    EXPORT ElapseTargets
    LIBRARY DESTINATION ${INSTALL_LIB_DIR}
    INCLUDES DESTINATION ${INSTALL_INC_DIR}
)
install(
    DIRECTORY ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse
    DESTINATION ${INSTALL_INC_DIR}
)
add_library(elapse::elapseplugin ALIAS elapseplugin)
