cmake_minimum_required(VERSION 3.23)
project(JustEnoughMod)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(SDL_ESD OFF)
set(SDL_RPI OFF)

file(GLOB SRC "src/*.cpp" "include/*.hpp")

add_subdirectory("vendor/bgfx")
add_subdirectory("vendor/sdl")

# Libary
add_library(${PROJECT_NAME} ${SRC} )

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries (${PROJECT_NAME} SDL2)
target_link_libraries (${PROJECT_NAME} bgfx)
target_link_libraries (${PROJECT_NAME} bimg)
target_link_libraries (${PROJECT_NAME} bx)

# Runtime
add_executable(${PROJECT_NAME}-bin "src/main.cpp")

target_include_directories(${PROJECT_NAME}-bin PUBLIC "include")

target_link_libraries (${PROJECT_NAME}-bin SDL2)
target_link_libraries (${PROJECT_NAME}-bin bgfx)
target_link_libraries (${PROJECT_NAME}-bin bimg)
target_link_libraries (${PROJECT_NAME}-bin bx)
