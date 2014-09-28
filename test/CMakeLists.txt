find_package(Qt5Test)
find_package(Qt5Widgets)
find_package(Threads)
include(CMakeParseArguments)

add_subdirectory(gmock)
include_directories(SYSTEM gmock)

set(ELAPSE_TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#
# Create a test, named according to the subdirectory it's in.
#
function(add_elapse_test)
    set(multiArgs SOURCES LIBRARIES INCLUDES COMPILE_OPTIONS DEPENDS)
    cmake_parse_arguments(TEST "" "" "${multiArgs}" ${ARGN})
    unset(multiArgs)

    get_filename_component(TEST_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
    set(TEST_NAME test_${TEST_NAME})

    add_executable(${TEST_NAME} 
        ${TEST_SOURCES} ${TEST_UNPARSED_ARGUMENTS}
        ${ELAPSE_TEST_SOURCE_DIR}/test_main.cpp
    )
    target_include_directories(${TEST_NAME} PRIVATE ${TEST_INCLUDES})
    target_link_libraries(${TEST_NAME} 
        Qt5::Test 
        gmock
        ${CMAKE_THREAD_LIBS_INIT}
        ${TEST_LIBRARIES}
        ${QXT_LIBRARIES}
    )
    target_compile_options(${TEST_NAME} PRIVATE ${TEST_COMPILE_OPTIONS})
    set_target_properties(${TEST_NAME} PROPERTIES AUTOMOC TRUE)
    add_dependencies(${TEST_NAME} "${TEST_DEPENDS}")
    add_test(${TEST_NAME} ${TEST_NAME})
endfunction()


#####  Tests  #####

add_subdirectory(bigendian24)
add_subdirectory(configdbus)
add_subdirectory(datasink)
add_subdirectory(pipeline)
add_subdirectory(pluginmanager)
add_subdirectory(python-bindings)
add_subdirectory(simpleeegfeatureextractor)
add_subdirectory(simplerawdatasinksource)
add_subdirectory(test_plugins)
add_subdirectory(udpdatasource)
