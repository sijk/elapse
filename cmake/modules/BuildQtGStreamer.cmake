include(ExternalProject)

ExternalProject_Add(build_qgst
    PREFIX ${CMAKE_BINARY_DIR}/3rdparty/qgst

    GIT_REPOSITORY http://anongit.freedesktop.org/git/gstreamer/qt-gstreamer.git
    GIT_TAG 0.10

    CMAKE_ARGS  -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
                -DQT_VERSION=5
                -DQTGSTREAMER_STATIC=ON
                -DQTGSTREAMER_EXAMPLES=OFF
                -DQTGSTREAMER_TESTS=OFF
                -DQTGSTREAMER_CODEGEN=OFF
                -DUSE_GST_PLUGIN_DIR=OFF
                -DUSE_QT_PLUGIN_DIR=OFF
    UPDATE_COMMAND ""
)

ExternalProject_Get_Property(build_qgst install_dir)
set(QGSt_DIR ${install_dir} CACHE PATH "QtGStreamer root directory")
unset(install_dir)

