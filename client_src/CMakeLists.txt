cmake_minimum_required(VERSION 3.0)

set(BINARY ${CMAKE_PROJECT_NAME}_client)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

file(COPY data/
        DESTINATION data/)

#add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run Qt5::Widgets SDL2 SDL2_image SDL2_ttf /usr/lib/x86_64-linux-gnu/libtiff.so.5 ${CMAKE_PROJECT_NAME}_common_lib)
#target_link_libraries(${BINARY}_run Qt5::Widgets SDL2 SDL2_image SDL2_ttf ${CMAKE_PROJECT_NAME}_common_lib)


install(FILES textures/bluestone.mat DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/greystone.mat DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/colorstone.mat DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/eagle.mat DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/mossy.mat DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/redbrick.mat DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wood.mat DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/purplestone.mat DESTINATION ${CMAKE_BINARY_DIR})