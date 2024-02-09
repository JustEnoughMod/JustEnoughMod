cmake_minimum_required(VERSION 3.23)
project(JustEnoughMod)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=mold")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fuse-ld=mold")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=mold")

set(SDL_ESD OFF)
set(SDL_RPI OFF)

file(GLOB SRC "src/*.c" "src/*.cpp" "src/*.h" "src/*.hpp")
add_executable(${PROJECT_NAME} ${SRC})

add_subdirectory("vendor/bgfx")
add_subdirectory("vendor/sdl")

target_include_directories(${PROJECT_NAME} PUBLIC "src")

target_link_libraries (${PROJECT_NAME} SDL2)
target_link_libraries (${PROJECT_NAME} bgfx)
target_link_libraries (${PROJECT_NAME} bimg)
target_link_libraries (${PROJECT_NAME} bx)
