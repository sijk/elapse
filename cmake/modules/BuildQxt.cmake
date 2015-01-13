include(ExternalProject)

ExternalProject_Add(build_qxt
    PREFIX ${CMAKE_BINARY_DIR}/3rdparty/qxt

    GIT_REPOSITORY https://bitbucket.org/libqxt/libqxt.git

    CONFIGURE_COMMAND <SOURCE_DIR>/configure -prefix <INSTALL_DIR> -static
                      -featuredir <INSTALL_DIR>/qmake/features
                      -no-xrandr -no-db -no-zeroconf
                      -nomake docs -nomake berkeley -nomake designer
                      -nomake widgets -nomake sql -nomake web -nomake zeroconf
    UPDATE_COMMAND ""
)

ExternalProject_Get_Property(build_qxt install_dir)
set(Qxt_DIR ${install_dir} CACHE PATH "Qxt root directory")
unset(install_dir)

