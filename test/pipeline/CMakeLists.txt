add_elapse_test(
    SOURCES     pipeline_test.cpp
    LIBRARIES   pipeline
                elapseplugin
    COMPILE_OPTIONS -Wno-unused-variable
)
