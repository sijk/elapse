find_package(Qt5Gui REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(Qxt REQUIRED)
find_package(Eigen3 REQUIRED)

set(elements_SRCS
    offlinedatasource.cpp
    featurextractor.cpp
    classifier.cpp
    datasink.cpp
)

set(elements_HDRS
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

qt5_wrap_cpp(elements_SRCS ${elements_HDRS})

add_library(elements SHARED ${elements_SRCS})
set_target_properties(elements PROPERTIES OUTPUT_NAME elapseelements)

target_include_directories(elements
    PUBLIC  ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${ELAPSE_COMMON_INCLUDE_DIRS}
)

target_link_libraries(elements
    PUBLIC  Qt5::Gui
    PRIVATE dbus
            Qxt::Core
)

target_compile_options(elements
    INTERFACE ${ELAPSE_CXX_FLAGS}
)

install(
    TARGETS elements
    EXPORT ElapseTargets
    LIBRARY DESTINATION ${INSTALL_LIB_DIR}
    INCLUDES DESTINATION ${INSTALL_INC_DIR}
)
install(
    DIRECTORY ${ELAPSE_ROOT_SOURCE_DIR}/include/elapse
    DESTINATION ${INSTALL_INC_DIR}
)
install(
    FILES ${QxtCore_INCLUDE_DIR}/qxtlogger.h
          ${QxtCore_INCLUDE_DIR}/qxtlogstream.h
          ${QxtCore_INCLUDE_DIR}/qxtglobal.h
    DESTINATION ${INSTALL_INC_DIR}/elapse/logging
)
add_library(elapse::elements ALIAS elements)
