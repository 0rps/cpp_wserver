file(GLOB SOURCES ./*.cpp)

add_executable(final ${SOURCES} ./config.h)

target_link_libraries(final -lrt)
