cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(RayTracer LANGUAGES CXX)

find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_STANDARD 11)

file(GLOB RAY_TRACER_SRC "*.h" "*.cpp")

add_executable(rayTracer ${RAY_TRACER_SRC})