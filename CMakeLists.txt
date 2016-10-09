cmake_minimum_required(VERSION 3.6)
project(aius_protocol)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wno-unused-variable")

set(SOURCE_FILES main.c packet.c io.c)
add_executable(aius_protocol ${SOURCE_FILES})