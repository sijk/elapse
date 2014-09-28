find_package(Qt5Widgets REQUIRED)

set(loggerwidget_SRCS
    logview.cpp
    logmodel.cpp
    logfilterproxymodel.cpp
    tablemodelloggerengine.cpp
)

set(loggerwidget_HDRS
    logview.h
    logmodel.h
    logfilterproxymodel.h
)

qt5_wrap_cpp(loggerwidget_SRCS ${loggerwidget_HDRS})
qt5_wrap_ui(loggerwidget_SRCS logview.ui)

add_library(loggerwidget STATIC ${loggerwidget_SRCS})

target_link_libraries(loggerwidget
    Qt5::Widgets
    ${QXT_LIBRARIES}
)
