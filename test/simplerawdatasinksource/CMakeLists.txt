add_elapse_test(
    SOURCES     simplerawdatasinksource_test.cpp
                ${ELAPSE_ROOT_SOURCE_DIR}/coreplugin/simplerawdatasink.cpp
                ${ELAPSE_ROOT_SOURCE_DIR}/coreplugin/simplerawdatasource.cpp
    LIBRARIES   elements
                Qt5::Widgets
    INCLUDES    ${ELAPSE_ROOT_SOURCE_DIR}/coreplugin
)
