cmake_minimum_required(VERSION 3.0)
project(${CMAKE_PROJECT_NAME}_server)

set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

file(COPY bot.lua
        DESTINATION bot.lua)

set(SOURCES ${SOURCES})

FIND_PACKAGE(Lua 5.3 REQUIRED)

add_executable(${PROJECT_NAME}_run ${SOURCES} ${LIB_SOURCES})

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME}_lib PUBLIC ${CMAKE_PROJECT_NAME}_common_lib )

target_link_libraries(${PROJECT_NAME}_run PUBLIC ${CMAKE_PROJECT_NAME}_common_lib yaml-cpp ${LUA_LIBRARY} )

