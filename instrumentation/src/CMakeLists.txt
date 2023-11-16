find_package(Clang REQUIRED) 

include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(Merlin SHARED Instrumentation.cpp Loop.cpp)

set_target_properties(Merlin PROPERTIES
    LINKER_LANGUAGE CXX COMPILE_FLAGS "-fno-rtti")