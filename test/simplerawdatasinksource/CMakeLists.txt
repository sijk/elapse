add_elapse_test(
    SOURCES     simplerawdatasinksource_test.cpp
                ${ELAPSE_ROOT_SOURCE_DIR}/coreplugin/src/simplerawdatasink.cpp
                ${ELAPSE_ROOT_SOURCE_DIR}/coreplugin/src/simplerawdatasource.cpp
    LIBRARIES   elements
                Qt5::Widgets
    INCLUDES    ${ELAPSE_ROOT_SOURCE_DIR}/coreplugin/src
)
