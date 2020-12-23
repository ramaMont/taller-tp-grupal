cmake_minimum_required(VERSION 3.10)

project(TPWOLFSTEIN)

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")

# Si se omite el include de abajo, los tests no pueden encontrar los headers
include_directories(common_src)
include_directories(server_src)
include_directories(client_src)
include_directories(editor_src)
include_directories(proxy)


include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
)
enable_testing()

add_subdirectory(common_src)
add_subdirectory(server_src)
add_subdirectory(client_src)
add_subdirectory(editor_src)
add_subdirectory(proxy)
add_subdirectory(tests)


