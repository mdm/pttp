cmake_minimum_required(VERSION 3.5)
project(pttp)
add_executable(${PROJECT_NAME} main.cpp window.cpp resource_manager.cpp renderer.cpp quad.cpp level.cpp texture.cpp)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(GLEW REQUIRED glew)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${GLEW_LIBRARIES})
