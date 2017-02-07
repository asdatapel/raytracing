cmake_minimum_required(VERSION 3.6)
project(raytracing)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCE_FILES main.cpp World.cpp Renderer.cpp MathHelper.cpp Ray.cpp Quaternion.cpp Quaternion.h Objects/Box.cpp Objects/Box.h)
LIST(APPEND SOURCE_FILES Shapes/Shape.cpp Shapes/Sphere.cpp Shapes/Triangle.cpp Objects/Object.cpp Objects/Wall.cpp)

include_directories(ext/glm)
include_directories(ext/glew/include)
include_directories(ext/SFML/include)

link_directories(ext/glew/lib)
link_directories(ext/SFML/lib)

add_executable(raytracing ${SOURCE_FILES})

find_package(OpenGL)

target_link_libraries(raytracing ${OPENGL_LIBRARIES})
target_link_libraries(raytracing GLEW.a)
target_link_libraries(raytracing sfml-system.a)
target_link_libraries(raytracing sfml-window.a)
target_link_libraries(raytracing sfml-graphics.a)