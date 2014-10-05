find_package(Qt5Gui REQUIRED)

set(pipeline_SRCS
    pipeline.cpp
)

set(pipeline_HDRS
    pipeline.h
)

qt5_wrap_cpp(pipeline_SRCS ${pipeline_HDRS})

add_library(pipeline STATIC ${pipeline_SRCS})

target_include_directories(pipeline
    PUBLIC  ${ELAPSE_CLIENT_SOURCE_DIR}/include
)

target_link_libraries(pipeline
    Qt5::Gui
)
