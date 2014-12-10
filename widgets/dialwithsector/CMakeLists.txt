find_package(Qt5Widgets REQUIRED)
find_package(Qwt REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(dialwithsector STATIC dialwithsector.cpp)

target_link_libraries(dialwithsector
    PUBLIC  Qt5::Widgets
            Qwt
)

