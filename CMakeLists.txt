cmake_minimum_required(VERSION 3.13)
project(new_doom C)

set(CMAKE_C_STANDARD 99)

include_directories(/Users/tvoronyu/new_doom/include)

#source_group(src)

include_directories(/Users/tvoronyu/new_doom/lib/SDL/SDL2_image.framework/Headers)
include_directories(/Users/tvoronyu/new_doom/lib/SDL/SDL2.framework/Headers)
include_directories(/Users/tvoronyu/new_doom/lib/SDL/SDL2_mixer.framework/Headers)
include_directories(/Users/tvoronyu/new_doom/lib/SDL/SDL2_ttf.framework/Headers)
include_directories(/Users/tvoronyu/new_doom/lib/libft/libft.h)

#set(SDL2_ROOT     "/Users/tvoronyu/new_doom/lib/SDL/")
#set(SDL2_Includes "${SDL2_ROOT}/SDL2.framework/Headers")
#set(SDL2_LibDir   "${SDL2_ROOT}")
#
#add_library(SDL2     STATIC IMPORTED)
#add_library(SDL2main STATIC IMPORTED)
#
#set_property(TARGET SDL2     PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/SDL2.a")


set(lib /Users/tvoronyu/new_doom/lib/SDL/SDL2_image.framework
        /Users/tvoronyu/new_doom/lib/SDL/SDL2.framework
        /Users/tvoronyu/new_doom/lib/SDL/SDL2_mixer.framework
        /Users/tvoronyu/new_doom/lib/SDL/SDL2_ttf.framework
        )


#target_include_directories(DOOMM SYSTEM PRIVATE ${SDL2_Includes})
# link against the SDL (and its dependencies)
#target_link_libraries(DOOMM ${DOOMM})
#set_property(TARGET SDL2main PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/SDL2main.a")

find_library(DOOMM ${lib})
#find_package(SDL2_)
#find_library(libsdl2 SDL2_image)
#find_library(libsdl /Users/tvoronyu/new_doom/lib/SDL/SDL2_image.framework/Headers/SDL2_image)

#include_directories(/Users/tvoronyu/CLionProjects/untitled7)

set(SOURCE_FILES /Users/tvoronyu/new_doom/src/main.c
        /Users/tvoronyu/new_doom/lib/libft/ft_bzero.c
        /Users/tvoronyu/new_doom/lib/SDL/SDL2_mixer.framework/SDL2_mixer
        /Users/tvoronyu/new_doom/lib/SDL/SDL2_mixer.framework/Headers/SDL_mixer.h
        /Users/tvoronyu/new_doom/src/ft_init_varible.c
        /Users/tvoronyu/new_doom/src/game.c
        /Users/tvoronyu/new_doom/src/jump.c
#        /Users/tvoronyu/new_doom/src/skybox.c
        /Users/tvoronyu/new_doom/src/get_next_line.c
        /Users/tvoronyu/new_doom/src/sdl.c
        /Users/tvoronyu/new_doom/lib/libft/ft_putendl.c
        /Users/tvoronyu/new_doom/lib/libft/ft_strchr.c
        /Users/tvoronyu/new_doom/lib/libft/ft_memchr.c
        /Users/tvoronyu/new_doom/lib/libft/ft_putendl_fd.c
        /Users/tvoronyu/new_doom/lib/libft/ft_strdup.c
        /Users/tvoronyu/new_doom/lib/libft/ft_strjoin.c
        /Users/tvoronyu/new_doom/lib/libft/ft_strnew.c
        /Users/tvoronyu/new_doom/lib/libft/ft_putstr_fd.c
        /Users/tvoronyu/new_doom/lib/libft/ft_strdel.c
        /Users/tvoronyu/new_doom/lib/libft/ft_strlen.c
        /Users/tvoronyu/new_doom/lib/libft/ft_memalloc.c
        /Users/tvoronyu/new_doom/lib/libft/ft_putchar_fd.c
        /Users/tvoronyu/new_doom/lib/libft/ft_strsub.c
        /Users/tvoronyu/new_doom/lib/libft/ft_memset.c
        /Users/tvoronyu/new_doom/lib/libft/ft_tolower.c
        /Users/tvoronyu/new_doom/lib/libft/ft_itoa.c
        /Users/tvoronyu/new_doom/lib/libft/ft_minus.c
        /Users/tvoronyu/new_doom/src/keys.c
        /Users/tvoronyu/new_doom/src/keys_2.c
        /Users/tvoronyu/new_doom/src/ft_fps.c
        )

link_directories(/Users/tvoronyu/new_doom/lib/SDL/SDL2_image.framework)


#set(SDL2_INCLUDE_DIR ~/.brew/include/SDL2/)
#set(SDL2_LIBRARY ~/.brew/lib/)
#include_directories(${SDL2_INCLUDE_DIR})
#link_directories(${SDL2_LIBRARY})
#add_executable(Nibbler main.cpp Game_sdl.hpp Game_sdl.cpp)
#target_link_libraries(DOOMM -lSDL2 -lSDL2_image)


add_executable(DOOMM ${SOURCE_FILES})

#target_link_libraries(DOOMM -lSDL2 -lSDL2_mixer)
target_link_libraries(DOOMM ${lib})
#target_link_libraries(DOOMM -lSDL2)
#target_link_libraries(DOOMM ${libsdl2})

#add_library(untitled7 src/game.c)
#add_subdirectory(untitled7/src)
#source_group(src/game.c)
#add_subdirectory(src)
#add_executable(untitled7 src/game.c)
#add_executable(untitled7 src/ft_fps.c)
#add_executable(untitled7 src/ft_init_varible.c)
#add_executable(untitled7 src/ft_valid.c)
#add_executable(untitled7 src/valid_help.c)
#add_executable(untitled7 src/valid_help_2.c)
#add_executable(untitled7 src/draw_map.c)
#add_executable(untitled7 src/sdl.c)
#add_executable(untitled7 src/get_next_line.c)
#add_executable(untitled7 src/keys.c)
#add_executable(untitled7 src/keys_2.c)
#add_executable(untitled7 src/raycast.c)
#add_executable(untitled7 src/raycast_2.c)