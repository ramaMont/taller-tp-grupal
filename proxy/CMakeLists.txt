set(BINARY ${CMAKE_PROJECT_NAME}_proxy)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

file(COPY textures/
        DESTINATION textures/)

add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run SDL2 SDL2_image ${CMAKE_PROJECT_NAME}_common_lib ${CMAKE_PROJECT_NAME}_client_lib ${CMAKE_PROJECT_NAME}_server_lib yaml-cpp)


install(FILES textures/bluestone.mat DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/greystone.mat DESTINATION ${CMAKE_BINARY_DIR})
