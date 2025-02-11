NAME = my_program
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = \
	main.c \
	c.c \
	colors.c \
	map_check.c \
	map_check2.c \
	print.c \
	string_funct.c \
	string_funct2.c \
	valid_map.c \
	get_next_line/get_next_line.c \
	start_game.c \

OBJ_FILES = $(SRC_FILES:.c=.o)
HEADER = my_header.h
GNL_PATH = get_next_line/
GNL_HEADER = $(GNL_PATH)get_next_line.h

LIBFT_PATH = libft
LIBFT_OBJ = $(LIBFT_PATH)/libft.a

MLX_PATH =  minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a

MLX_FLAGS = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT_OBJ) $(MLX_FLAGS)

%.o: %.c $(HEADER) $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_OBJ):
	@if [ ! -f "$(LIBFT_OBJ)" ]; then $(MAKE) -C $(LIBFT_PATH); fi

$(MLX_LIB):
	@if [ ! -f "$(MLX_LIB)" ]; then $(MAKE) -C $(MLX_PATH); fi

clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	@if [ -f "$(LIBFT_OBJ)" ]; then $(MAKE) -C $(LIBFT_PATH) fclean; fi
	@if [ -f "$(MLX_LIB)" ]; then $(MAKE) -C $(MLX_PATH) clean; fi

re: fclean all

.PHONY: all clean fclean re
