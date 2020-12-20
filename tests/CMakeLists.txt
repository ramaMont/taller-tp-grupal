set(BINARY ${CMAKE_PROJECT_NAME}_tests)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline")

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME unit COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_server_lib ${CMAKE_PROJECT_NAME}_client_lib ${CMAKE_PROJECT_NAME}_common_lib ${CMAKE_PROJECT_NAME}_editor_lib gtest_main yaml-cpp  ${LUA_LIBRARY})
