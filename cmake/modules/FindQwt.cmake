if(Qwt_DIR)
    list(INSERT CMAKE_PREFIX_PATH 0 ${Qwt_DIR})
endif()

find_path(QWT_INCLUDE_DIR qwt.h)
find_library(QWT_LIBRARY qwt)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Qwt DEFAULT_MSG QWT_LIBRARY QWT_INCLUDE_DIR)

if(QWT_FOUND AND NOT TARGET Qwt)
    add_library(Qwt STATIC IMPORTED)
    set_target_properties(Qwt PROPERTIES
        IMPORTED_LOCATION ${QWT_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${QWT_INCLUDE_DIR}
    )
endif()

