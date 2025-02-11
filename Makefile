NAME = my_program
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = \
	main.c \
	c.c \
	colors.c \
	ft_atoi.c \
	map_check.c \
	map_check2.c \
	print.c \
	string_funct.c \
	string_funct2.c \
	valid_map.c \
	get_next_line/get_next_line.c \

OBJ_FILES = $(SRC_FILES:.c=.o)
HEADER = my_header.h
GNL_PATH = get_next_line/
GNL_HEADER = $(GNL_PATH)get_next_line.h

# Path to libft directory and object files
LIBFT_PATH = libft
LIBFT_OBJ = $(LIBFT_PATH)/libft.a

# All files needed to build
OBJ_FILES += $(LIBFT_OBJ)  # Add libft.a to object files for linking

# All compilation and linking
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

# Rule for compiling .o files
%.o: %.c $(HEADER) $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling libft.a (only if needed)
$(LIBFT_OBJ):
	$(MAKE) -C $(LIBFT_PATH)

# Clean up object files
clean:
	rm -f $(OBJ_FILES)

# Clean everything (including libft)
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_PATH)/libft.a

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
