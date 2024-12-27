# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 19:27:00 by yyean-wa          #+#    #+#              #
#    Updated: 2024/12/27 23:00:07 by yyean-wa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
ASAN = -fsanitize=address -g3
CFLAGS = -Wall -Werror -Wextra $(ASAN)

SRCS =	ft_isalpha.c ft_isdigit.c\
		ft_isalnum.c ft_isascii.c\
		ft_isprint.c ft_strlen.c\
		ft_memset.c ft_bzero.c\
		ft_memcpy.c ft_memmove.c\
		ft_strlcpy.c ft_strlcat.c\
		ft_toupper.c ft_tolower.c\
		ft_strchr.c ft_strrchr.c\
		ft_strncmp.c ft_memchr.c\
		ft_memcmp.c ft_strnstr.c\
		ft_atoi.c ft_calloc.c\
		ft_strdup.c ft_substr.c\
		ft_strjoin.c ft_strtrim.c\
		ft_split.c ft_itoa.c\
		ft_strmapi.c ft_striteri.c\
		ft_putchar_fd.c ft_putstr_fd.c\
		ft_putendl_fd.c ft_putnbr_fd.c\
		ft_strpos.c
OBJS := ${SRCS:.c=.o}

BONUS =	ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c
BONUSOBJT := ${BONUS:.c=.o}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

LIBC = ar rcs
REMOVE = rm -rf

GREEN='\033[1;92m'
YELLOW='\033[0;93m'
RESET = '\033[0;0m'

all: $(NAME)

$(NAME): ${OBJS}
	@${LIBC} $(NAME) ${OBJS}
	@echo $(GREEN)"Libft mandatory ready."$(RESET)

bonus: ${OBJS} ${BONUSOBJT}
	@${LIBC} $(NAME) ${BONUSOBJT}
	@echo $(GREEN)"Libft bonus ready."$(RESET)

debug: CFLAGS += $(ASAN)
debug: clean ${OBJS} ${BONUSOBJT}
	@${LIBC} $(NAME) ${OBJS} ${BONUSOBJT}
	@echo $(GREEN)"Libft (with ASAN) ready."$(RESET)

clean:
	@${REMOVE} ${OBJS} ${BONUSOBJT}
	@echo $(YELLOW)"Remove libft's objs file"$(RESET)

fclean: clean
	@${REMOVE} $(NAME)
	@echo $(YELLOW)"Remove library libft"$(RESET)

re: fclean all

.PHONY: bonus all clean fclean re debug
