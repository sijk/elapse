find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Qwt REQUIRED)
find_package(Qxt REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc)

set(widgets_SRCS
    cvmatwidget/cvmatwidget.cpp
    dialwithsector/dialwithsector.cpp
    headwidget/headwidget.cpp
    headwidget/headmesh.cpp
    spinner/spinner.cpp
    stripchart/stripchart.cpp
    util/ratelimiter.cpp
)

set(widgets_HDRS
    cvmatwidget/cvmatwidget.h
    dialwithsector/dialwithsector.h
    headwidget/headwidget.h
    headwidget/headmesh.h
    spinner/spinner.h
    stripchart/stripchart.h
    util/ratelimiter.h
)

qt5_wrap_cpp(widgets_SRCS ${widgets_HDRS})
qt5_add_resources(widgets_SRCS spinner/spinner.qrc)

add_library(widgets SHARED ${widgets_SRCS})

target_link_libraries(widgets
    PUBLIC  Qt5::Widgets
            Qt5::OpenGL
            Qwt
            ${OpenCV_LIBRARIES}
    PRIVATE ${OPENGL_gl_LIBRARY}
            Qxt::Core
)

target_include_directories(widgets
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dialwithsector>
              $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headwidget>
              $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/spinner>
              $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stripchart>
    PUBLIC    ${OpenCV_INCLUDE_DIRS}
)

set_target_properties(widgets PROPERTIES OUTPUT_NAME elapsewidgets)

install(
    TARGETS widgets
    EXPORT ElapseTargets
    LIBRARY DESTINATION ${INSTALL_LIB_DIR}
    INCLUDES DESTINATION ${INSTALL_INC_DIR}
)
install(
    FILES cvmatwidget/cvmatwidget.h
          dialwithsector/dialwithsector.h
          headwidget/headwidget.h
          spinner/spinner.h
          stripchart/stripchart.h
    DESTINATION ${INSTALL_INC_DIR}/elapse/widgets
)

add_library(elapse::widgets ALIAS widgets)
