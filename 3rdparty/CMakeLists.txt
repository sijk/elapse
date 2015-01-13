# Build the ExternalProject dependencies

if(QGSt_DIR)
    list(INSERT CMAKE_PREFIX_PATH 0 ${QGSt_DIR})
endif()

find_package(Qxt QUIET)
find_package(Qwt QUIET)
find_package(Qt5GStreamer QUIET)

if(NOT QXT_FOUND OR NOT QWT_FOUND OR NOT QTGSTREAMER_FOUND)
    include(BuildQxt)
    include(BuildQwt)
    include(BuildQtGStreamer)

    add_custom_target(require_reconf ALL
        DEPENDS build_qxt build_qwt build_qgst
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_LIST_FILE}
        COMMENT "Built dependencies. Now rebuild to build this project."
    )

    set(NEEDS_REBUILD TRUE PARENT_SCOPE)
endif()
