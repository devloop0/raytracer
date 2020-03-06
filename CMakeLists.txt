cmake_minimum_required(VERSION 3.0)
project(raytracer)

include_directories(include)

set(SOURCES
	src/bounding_box.cpp
	src/ray.cpp
	src/scene.cpp
	src/sphere_object.cpp
	src/scene_object.cpp
	src/image.cpp
	src/main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(raytracer ${SOURCES})
