project(Blockchain_src)

set(HEADER_FILES Hash.h StringGenerator.h Application.h Benchmark.h StringComparator.h Color.h)

set(SOURCE_FILES Hash.cpp StringGenerator.cpp Application.cpp Benchmark.cpp StringComparator.cpp Color.cpp)

add_library(Blockchain_src STATIC ${SOURCE_FILES} ${HEADER_FILES})