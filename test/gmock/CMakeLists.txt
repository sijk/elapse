add_library(gmock SHARED gmock-gtest-all.cc)
target_compile_options(gmock PRIVATE -Wno-missing-field-initializers)
