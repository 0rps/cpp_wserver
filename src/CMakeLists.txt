file(GLOB SOURCES ./*.cpp)

add_executable(wserver ${SOURCES})

target_link_libraries(wserver -lrt)
