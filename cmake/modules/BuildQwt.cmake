include(ExternalProject)

ExternalProject_Add(build_qwt
    PREFIX ${CMAKE_BINARY_DIR}/3rdparty/qwt

    SVN_REPOSITORY svn://svn.code.sf.net/p/qwt/code/branches/qwt-6.1

    PATCH_COMMAND sed -i -e "s:/usr/local/.*:<INSTALL_DIR>:"
                  -e "/QwtDll/ s/^/#/"
                  -e "/QwtSvg/ s/^/#/"
                  -e "/QwtDesigner/ s/^/#/"
                  <SOURCE_DIR>/qwtconfig.pri
    CONFIGURE_COMMAND qmake <SOURCE_DIR>/qwt.pro
    UPDATE_COMMAND ""
)

ExternalProject_Get_Property(build_qwt install_dir)
set(Qwt_DIR ${install_dir} CACHE PATH "Qwt root directory")
unset(install_dir)

