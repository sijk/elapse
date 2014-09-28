find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

set(headwidget_SRCS
    headwidget.cpp
    headmesh.cpp
)

set(headwidget_HDRS
    headwidget.h
)

qt5_wrap_cpp(headwidget_SRCS ${headwidget_HDRS})

add_library(headwidget STATIC ${headwidget_SRCS})

target_link_libraries(headwidget
    PUBLIC  Qt5::Widgets
            Qt5::OpenGL
    PRIVATE ${OPENGL_gl_LIBRARY}
)
