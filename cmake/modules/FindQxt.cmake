find_package(Threads REQUIRED)

if(Qxt_DIR)
    list(INSERT CMAKE_PREFIX_PATH 0 ${Qxt_DIR})
endif()

set(QxtNetwork_MOD_DEPS     Core)
set(QxtWidgets_MOD_DEPS     Core)
set(QxtWeb_MOD_DEPS         Core Network)
set(QxtZeroConf_MOD_DEPS    Core Network)
set(QxtSql_MOD_DEPS         Core)
set(QxtBerkeley_MOD_DEPS    Core)

set(QxtCore_LIB_DEPS        Qt5::Core ${CMAKE_THREAD_LIBS_INIT})
set(QxtNetwork_LIB_DEPS     Qt5::Network)

# Handle COMPONENTS arguments to find_package()
set(QXT_MODULES Core)
if(Qxt_FIND_COMPONENTS)
    foreach(comp ${Qxt_FIND_COMPONENTS})
        list(APPEND QXT_MODULES ${comp})
        foreach(dep ${Qxt${comp}_MOD_DEPS})
            list(APPEND QXT_MODULES ${dep})
        endforeach()
    endforeach()
    list(REMOVE_DUPLICATES QXT_MODULES)
endif()

# Find the requested modules
set(QXT_MODULE_VARS)
foreach(mod ${QXT_MODULES})
    # Find the library
    find_library(Qxt${mod}_LIBRARY Qxt${mod})

    # Find the include path
    find_path(Qxt${mod}_INCLUDE_DIR Qxt${mod}/Qxt${mod})
    set(Qxt${mod}_INCLUDE_DIR ${Qxt${mod}_INCLUDE_DIR}/Qxt${mod})

    # Store the variable names for later
    list(APPEND QXT_MODULE_VARS Qxt${mod}_LIBRARY Qxt${mod}_INCLUDE_DIR)

    # Add Qxt module dependencies to library dependencies
    foreach(dep ${Qxt${mod}_MOD_DEPS})
        list(APPEND Qxt${mod}_LIB_DEPS Qxt::${mod})
    endforeach()
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Qxt DEFAULT_MSG ${QXT_MODULE_VARS})
mark_as_advanced(${QXT_MODULE_VARS})

# Create imported library targets for the modules
if(QXT_FOUND)
    foreach(mod ${QXT_MODULES})
        if(NOT TARGET Qxt::${mod})
            add_library(Qxt::${mod} STATIC IMPORTED)
            set_target_properties(Qxt::${mod} PROPERTIES
                IMPORTED_LOCATION ${Qxt${mod}_LIBRARY}
                INTERFACE_INCLUDE_DIRECTORIES ${Qxt${mod}_INCLUDE_DIR}
                INTERFACE_LINK_LIBRARIES "${Qxt${mod}_LIB_DEPS}"
            )
        endif()
    endforeach()
endif()

