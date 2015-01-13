find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5GStreamer REQUIRED)
find_package(Qxt REQUIRED)
find_package(PkgConfig)
pkg_search_module(GSTREAMER REQUIRED gstreamer-0.10)

set(coreplugin_SRCS
    udpdatasource.cpp
    simplerawdatasource.cpp
    eegdecoder.cpp
    videodecoder.cpp
    imudecoder.cpp
    dummyeegfeatureextractor.cpp
    dummyvideofeatureextractor.cpp
    dummyimufeatureextractor.cpp
    dummyclassifier.cpp
    dummyaction.cpp
    blackholedatasink.cpp
    simplerawdatasink.cpp
    util/gstwrappedbuffer.cpp
)

qt5_wrap_cpp(coreplugin_SRCS coreplugin.h)

add_library(coreplugin STATIC ${coreplugin_SRCS})

target_include_directories(coreplugin
    PRIVATE ${GSTREAMER_INCLUDE_DIRS}
            ${QTGSTREAMER_INCLUDE_DIR}
)

target_link_libraries(coreplugin
    PRIVATE widgets
            Qt5::Widgets
            Qt5::Network
            Qxt::Core
            ${GSTREAMER_LIBRARIES}
            ${QTGSTREAMER_LIBRARIES}
            ${QTGSTREAMER_UI_LIBRARIES}
            ${QTGSTREAMER_UTILS_LIBRARIES}
)

target_compile_definitions(coreplugin PRIVATE QT_STATICPLUGIN QT_PLUGIN)

set_target_properties(coreplugin PROPERTIES AUTOMOC TRUE)

# Ignore -pedantic warnings from within QtGStreamer
set_source_files_properties(
    videodecoder.cpp util/gstwrappedbuffer.cpp
    PROPERTIES COMPILE_FLAGS -Wno-pedantic
)
