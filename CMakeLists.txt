cmake_minimum_required(VERSION 3.13)
project(untitled7 C)

set(CMAKE_C_STANDARD 99)

include_directories(/Users/tvoronyu/CLionProjects/untitled7/include)

#source_group(src)

include_directories(lib/SDL/SDL2.framework/Headers)
include_directories(lib/SDL/SDL2_image.framework/Headers)
include_directories(lib/SDL/SDL2_mixer.framework/Headers)
include_directories(lib/SDL/SDL2_ttf.framework/Headers)
include_directories(lib/libft/libft.h)
include_directories(include/wolf3d.h)

#include_directories(/Users/tvoronyu/CLionProjects/untitled7)


add_executable(untitled7 src/main.c)