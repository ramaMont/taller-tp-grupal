cmake_minimum_required(VERSION 3.0)
set(BINARY ${CMAKE_PROJECT_NAME}_editor)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")


file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

# Si incluyo los source en la lib, explota por alguna razon, no encuentra 
# las cosas de Qt.
add_library(${BINARY}_lib)
# add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run Qt5::Widgets yaml-cpp ${CMAKE_PROJECT_NAME}_common_lib)

