add_elapse_test(
    SOURCES     pipeline_test.cpp
    LIBRARIES   pipeline
                elements
    COMPILE_OPTIONS -Wno-unused-variable
)
