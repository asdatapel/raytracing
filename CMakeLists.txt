cmake_minimum_required(VERSION 3.6)
project(testcl)

set(CMAKE_CXX_STANDARD 11)

include_directories(ext/SFML/include)

link_directories(ext/SFML/lib)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

set(SOURCE_FILES main.cpp)
add_executable(raytracing ${SOURCE_FILES})
target_link_libraries (raytracing ${OpenCL_LIBRARY})
target_link_libraries(raytracing sfml-system.a)
target_link_libraries(raytracing sfml-window.a)
target_link_libraries(raytracing sfml-graphics.a)