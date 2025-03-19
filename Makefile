# Colours
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YEL			=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

# Program
NAME	= cub3D

# Compilation flags
CC		= cc
CFLAGS	= -Werror -Wextra -Wall -g3 #-fsanitize=address
MAKEFLAGS 		+= --silent

# Structure
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

SRC_PATH = ./src/
SRC = \
	./src/main.c \
	./src/check_parse/check_input.c \
	./src/check_parse/check_map_borders.c \
	./src/check_parse/check_map_contents.c \
	./src/check_parse/check_textures.c \
	./src/check_parse/generate_map.c \
	./src/check_parse/parse_input.c \
	./src/check_parse/process_cub_file.c \
	./src/check_parse/set_ceiling_floor_colours.c \
	./src/dynamics/key_input_handler.c \
	./src/dynamics/movement.c \
	./src/dynamics/position.c \
	./src/dynamics/rotation.c \
	./src/exit/error.c \
	./src/exit/exit.c \
	./src/exit/free.c \
	./src/graphics/texture.c \
	./src/graphics/ray_cast.c \
	./src/graphics/render.c \
	./src/init/init_main.c \
	./src/init/init_directions.c \
	./src/init/init_mlx.c \
	./src/init/init_ray_textures.c

SRCS	= $(SRC)

OBJ_PATH	= ./obj/
OBJ		= $(patsubst $(SRC_PATH)%, %, $(SRCS:.c=.o))
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC			=	-I ./inc/\
				-I ./libft/\
				-I ./minilibx-linux/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Create object directories
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) $(shell find $(SRC_PATH) -type d | sed "s|$(SRC_PATH)|$(OBJ_PATH)|")

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@printf "$(B)$(GREEN)$(NAME) binaries compiled$(D)\n"

# Other rules
$(LIBFT):
	make -sC $(LIBFT_PATH)

$(MLX):
	make -sC $(MLX_PATH)

# Cleaning
clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME) valgrind_out.txt
	make -C $(LIBFT_PATH) fclean

re: fclean all

# Valgrind rule
valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --num-callers=20 --log-file=valgrind_out.txt ./cub3D ./maps/pass/corridors.cub

.PHONY: all re clean fclean bonus test valgrind