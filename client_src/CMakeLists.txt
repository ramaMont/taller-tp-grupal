set(BINARY ${CMAKE_PROJECT_NAME}_client)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

file(COPY textures/
        DESTINATION textures/)

add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run SDL2 SDL2_image ${CMAKE_PROJECT_NAME}_common_lib)


install(FILES textures/bluestone_r.txt DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/bluestone_g.txt DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/bluestone_b.txt DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/greystone_r.txt DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/greystone_g.txt DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/greystone_b.txt DESTINATION ${CMAKE_BINARY_DIR})

