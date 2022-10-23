cmake_minimum_required(VERSION 3.0.0)
project(PASSWORD_GENERATOR VERSION 0.1.0)

add_compile_options(/sdl-)
add_executable(pw_gen pw_gen.h settings.h pw_gen.cpp)
