file(GLOB SOURCES ./*.cpp)

add_executable(final ${SOURCES})

target_link_libraries(final -lrt)
