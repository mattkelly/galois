cmake_minimum_required(VERSION 2.6)
project(galois)

set(CMAKE_C_FLAGS "-Wall -Werror")

include_directories(src)

add_executable(main src/gf_math.c src/main.c)

