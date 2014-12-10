find_package(Qt5Widgets REQUIRED)

set(spinner_SRCS
    spinner.cpp
)

set(spinner_HDRS
    spinner.h
)

qt5_wrap_cpp(spinner_SRCS ${spinner_HDRS})
qt5_add_resources(spinner_SRCS spinner.qrc)

add_library(spinner STATIC ${spinner_SRCS})

target_link_libraries(spinner
    PUBLIC  Qt5::Widgets
)

