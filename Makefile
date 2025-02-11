NAME = my_program
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = \
	main.c \
	c.c \
	colors.c \
	ft_atoi.c \
	lib_ft.c \
	map_check.c \
	map_check2.c \
	print.c \
	string_funct.c \
	string_funct2.c \
	valid_map.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)
HEADER = my_header.h
GNL_PATH = get_next_line/
GNL_HEADER = $(GNL_PATH)get_next_line.h

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

%.o: %.c $(HEADER) $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
