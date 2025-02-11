# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olomova <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 15:38:22 by olomova           #+#    #+#              #
#    Updated: 2024/02/21 15:38:30 by olomova          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= ft_memset ft_bzero ft_memcpy ft_memmove ft_memchr ft_memcmp ft_strlen ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp ft_strlcpy ft_strlcat ft_strnstr ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim ft_itoa ft_strmapi ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_atoi ft_split ft_striteri 

SRCS		= $(addsuffix .c, ${SRC})

HEAD		= ./includes/ 

OBJS		= ${SRCS:.c=.o}

NAME		= libft.a

CC			= gcc
RM			= rm -f
AR			= ar rc
RN			= ranlib

CFLAGS		= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}
			${RN} ${NAME}

.phony: all
all:		$(NAME)

.phony: clean
clean:
			${RM} ${OBJS}

.phony: fclean
fclean:		clean
			${RM} $(NAME)

.phony: re
re:			fclean all
