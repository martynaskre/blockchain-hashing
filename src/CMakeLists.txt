project(Blockchain_src)

set(HEADER_FILES Hash.h)

set(SOURCE_FILES Hash.cpp)

add_library(Blockchain_src STATIC ${SOURCE_FILES} ${HEADER_FILES})