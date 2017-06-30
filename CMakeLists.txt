cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(RayTracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

file(GLOB RAY_TRACER_SRC "*.h" "*.cpp")

add_executable(rayTracer ${RAY_TRACER_SRC})