cmake_minimum_required(VERSION 3.23)
project(JustEnoughMod)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(SDL2 REQUIRED)

file(GLOB SRC "src/*.c" "src/*.cpp" "src/*.h" "src/*.hpp")
add_executable(${PROJECT_NAME} ${SRC})

add_subdirectory("vendor/bgfx")

target_include_directories(${PROJECT_NAME} PUBLIC "src")
# target_include_directories(${PROJECT_NAME} PUBLIC "vendor/bgfx")

target_link_libraries (${PROJECT_NAME} bx)
target_link_libraries (${PROJECT_NAME} bgfx)
target_link_libraries (${PROJECT_NAME} bimg)
target_link_libraries (${PROJECT_NAME} SDL2)