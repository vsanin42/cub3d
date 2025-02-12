# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 13:46:14 by vsanin            #+#    #+#              #
#    Updated: 2025/02/12 13:46:14 by vsanin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

MLXDIR = mlx
MLX = $(MLXDIR)/libmlx_Linux.a
MLX_FLAGS = -L/usr/lib/X11 -lXext -lX11

HEADER = includes/cub3d.h

SRC  = 	srcs/main.c \
		srcs/c.c \
		srcs/colors.c \
		srcs/map_check.c \
		srcs/map_check2.c \
		srcs/print.c \
		srcs/string_funct.c \
		srcs/string_funct2.c \
		srcs/valid_map.c \
		srcs/start_game.c \

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLX):
	$(MAKE) -C $(MLXDIR)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I/usr/include -Imlx

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(MLXDIR) clean

re: fclean all

.PHONY: all clean fclean re