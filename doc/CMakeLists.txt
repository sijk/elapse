find_package(Doxygen)
find_package(Java COMPONENTS Runtime)

add_custom_target(plantuml
    COMMAND ${Java_JAVA_EXECUTABLE}
            -Djava.awt.headless=true
            -jar ${ELAPSE_ROOT_SOURCE_DIR}/tools/plantuml.jar
            -v -Sshadowing=false
            -o ${CMAKE_CURRENT_BINARY_DIR}/img
            "${ELAPSE_ROOT_SOURCE_DIR}/**.(c|cpp|h|dox)"
    VERBATIM
)

configure_file(Doxyfile.in Doxyfile @ONLY)

if(BUILD_DOCS)
    set(_ALL_IF_BUILD_DOCS ALL)
endif()

add_custom_target(docs
    ${_ALL_IF_BUILD_DOCS}
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    VERBATIM
    DEPENDS plantuml
)

install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html ${CMAKE_CURRENT_BINARY_DIR}/img
    DESTINATION ${INSTALL_DOC_DIR}
    OPTIONAL
)
