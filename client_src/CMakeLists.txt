cmake_minimum_required(VERSION 2.8)

project(qt-sdl)
find_package(Qt5Widgets)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sdldemo
  src/texture.cpp
  src/exception.cpp
  src/window.cpp
  src/camera.cpp
  src/coordinates.cpp
  src/player.cpp
  src/ray.cpp
  src/ray_casting.cpp
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (show_animation
  src/mainshow_animation.cpp  
)

add_executable (show_image
  src/mainshow_image.cpp  
)

add_executable (ray_casting
  src/mainray_casting.cpp
)


target_link_libraries(show_image Qt5::Widgets)
target_link_libraries(show_image sdldemo SDL2 SDL2_image)

target_link_libraries(show_animation sdldemo SDL2 SDL2_image)
target_link_libraries(show_animation Qt5::Widgets)

target_link_libraries(ray_casting sdldemo SDL2 SDL2_image)
target_link_libraries(ray_casting Qt5::Widgets)

install(FILES textures/wolfstein.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein0.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein1.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein2.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein3.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein4.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein5.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein6.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein7.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein8.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein9.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein10.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein11.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein12.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein13.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein14.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein15.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein16.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein17.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein18.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein19.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein20.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein21.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein22.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein23.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein24.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein25.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein26.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein27.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein28.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein29.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES textures/wolfenstein30.jpg DESTINATION ${CMAKE_BINARY_DIR})

