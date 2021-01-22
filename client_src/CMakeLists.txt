cmake_minimum_required(VERSION 3.0)

set(BINARY ${CMAKE_PROJECT_NAME}_client)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})


#add_library(${BINARY}_lib STATIC ${SOURCES})
#add_library(${BINARY}_lib)

target_link_libraries(${BINARY}_run Qt5::Widgets SDL2 SDL2_image SDL2_ttf yaml-cpp /usr/lib/x86_64-linux-gnu/libtiff.so.5 ${CMAKE_PROJECT_NAME}_common_lib)
#target_link_libraries(${BINARY}_run Qt5::Widgets SDL2 SDL2_image SDL2_ttf ${CMAKE_PROJECT_NAME}_common_lib)