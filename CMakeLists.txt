cmake_minimum_required(VERSION 3.23)
project(JustEnoughMod)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("vendor/bgfx")

file(GLOB SRC "src/*.c" "src/*.cpp" "src/*.h" "src/*.hpp")
add_executable(JustEnoughMod ${SRC})

target_include_directories(JustEnoughMod PUBLIC "src")

# target_link_libraries (JustEnoughMod bgfx)