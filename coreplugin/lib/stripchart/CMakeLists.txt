find_package(Qt5Widgets REQUIRED)
find_package(Qwt REQUIRED)

set(stripchart_SRCS
    stripchart.cpp
)

set(stripchart_HDRS
    stripchart.h
)

qt5_wrap_cpp(stripchart_SRCS ${stripchart_HDRS})

add_library(stripchart STATIC ${stripchart_SRCS})

target_link_libraries(stripchart
    PUBLIC  Qt5::Widgets
    PRIVATE Qwt
)
