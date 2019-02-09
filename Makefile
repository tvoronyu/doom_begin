NAME = wolf3d

SRC_WOLF = ./src/main.c \
			./src/get_next_line.c \
			./src/ft_valid.c \
			./src/valid_help.c \
			./src/valid_help_2.c \
			./src/game.c \
			./src/sdl.c \
			./src/init.c \
			./src/texture.c \
			./src/ft_game_js.c \

OBJECT_WOLF = $(SRC_WOLF:.c=.o)

# FLAGS = -Wall -Wextra

INCLUDES_WOLF = -I ./include/

INCLUDES_LIBFT = -I ./lib/libft/

INCLUDES_SDL2 = -I ./lib/SDL/SDL2.framework/Headers

INCLUDES_SDL2_IMAGE = -I ./lib/SDL/SDL2_image.framework/Headers

INCLUDES_SDL2_MIXER = -I ./lib/SDL/SDL2_mixer.framework/Headers

LIBFT = ./lib/libft/libft.a

INCLUDES_SDL2_TTF = -I ./lib/SDL/SDL2_ttf.framework/Headers

FRAMEWORK_SDL2 = -F ./lib/SDL -framework SDL2 \
	-framework SDL2_image \
	-framework SDL2_ttf \
	-framework SDL2_mixer

FF = SDL2 \
	SDL2_image \

FRAMEWORK_MLX = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME) : $(OBJECT_WOLF)
	make -C ./lib/libft
	@echo "file: */Wolf"
	@gcc -o $(NAME) $(FLAGS) $(LIBFT) $(INCLUDES_SDL2) $(INCLUDES_SDL2_IMAGE) -rpath @loader_path/lib/sdl $(FRAMEWORK_SDL2) $(OBJECT_WOLF) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

%.o: %.c includes/*.h
	gcc -g $(FLAGS) -o $@ -c $< $(INCLUDES_WOLF) $(INCLUDES_SDL2) $(INCLUDES_LIBFT) \
$(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

%.o: %.c
	gcc -g 	$(FLAGS) -o $@ -c $< $(INCLUDES_WOLF) $(INCLUDES_SDL2) $(INCLUDES_LIBFT) \
$(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

	@echo "Wolf compiled"
clean:
	make -C ./lib/libft clean
	/bin/rm -f $(OBJECT_WOLF)

fclean: clean
	/bin/rm -f ./lib/libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all

# tags:
# 	etags -R *.c *.h

# NAME = wolf3d

# SRC_WOLF = main.c \
# 			lib/get_next_line.c \
# 			ft_valid.c \
# 			valid_help.c \
# 			valid_help_2.c \
# 			game.c \
# 			sdl.c \

# OBJECT_WOLF = $(SRC_WOLF:.c=.o)

# # FLAGS = -Wall -Wextra -Werror

# INCLUDES_WOLF = -I ./include/wolf3d.h

# INCLUDES_LIBFT = -I ./lib/libft/

# INCLUDES_SDL2 = -I ./include/SDL/SDL2.framework/Headers

# INCLUDES_SDL2_IMAGE = -I ./include/SDL/SDL2_image.framework/Headers

# INCLUDES_SDL2_MIXER = -I ./include/DL/SDL2_mixer.framework/Headers

# INCLUDES_SDL2_TTF = -I ./include/SDL/SDL2_ttf.framework/Headers

# LIBFT = ./lib/libft/libft.a


# FRAMEWORK_SDL2 = -F ./include/SDL \
# 	-framework SDL2 \
# 	-framework SDL2_image \
# 	-framework SDL2_ttf \
# 	-framework SDL2_mixer

# # FRAMEWORK_SDL2 = SDL2

# FRAMEWORK_MLX = -lmlx -framework OpenGL -framework AppKit

# all: $(NAME)

# $(NAME) : $(OBJECT_WOLF)
# 	make -C ./lib/libft
# 	@echo "file: */Wolf"
# 	@gcc -o $(NAME) $(FLAGS)  $(LIBFT) $(INCLUDES_SDL2) $(INCLUDES_SDL2_IMAGE) -rpath @loader_path/sdl $(FRAMEWORK_SDL2) $(OBJECT_WOLF) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)
# 	./wolf3d map_first.fdf

# %.o: %.c *.h
# 	gcc -g $(FLAGS) -o $@ -c $< $(INCLUDES_WOLF) $(INCLUDES_SDL2)  $(INCLUDES_LIBFT \
# $(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

# %.o: %.c
# 	gcc -g 	$(FLAGS) -o $@ -c $< $(INCLUDES_WOLF) $(INCLUDES_SDL2)  $(INCLUDES_LIBFT \
# $(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

# 	@echo "Wolf compiled"
# clean:
# 	make -C ./lib/libft clean
# 	/bin/rm -f $(OBJECT_WOLF)
# 	rm -f TAGS

# fclean: clean
# 	/bin/rm -f ./lib/libft/libft.a
# 	/bin/rm -f $(NAME)

# re: fclean all tags

