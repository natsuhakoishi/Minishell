# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 17:37:04 by yyean-wa          #+#    #+#              #
#    Updated: 2024/12/26 22:13:25 by yyean-wa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

AR = ar rcs
RM = rm -rf
ASAN = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror -I./includes/ -I/usr/include/readline/ #$(ASAN)

SRC_FILES = main lexer parser expansion \
			execution redirect built-in built-in_2 child_process \
			signal free_exit utils
SRC = $(addprefix src/, $(addsuffix .c,  $(SRC_FILES)))

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

#object files
OBJ_DIR = objs/
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@cc $(CFLAGS) -c $< -o $@

GREEN='\033[1;92m'
YELLOW='\033[0;93m'
RESET = '\033[0;0m'

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@cc $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)
	@echo $(GREEN)"Minishell ready."$(RESET)

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make bonus -C $(LIBFT_PATH)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJ_DIR)
	@echo  $(YELLOW)"Remove objs file"$(RESET)

fclean: clean
	@make fclean -C $(LIBFT_PATH) | grep -v "Remove libft's objs file"
	@$(RM) $(NAME)
	@echo $(YELLOW)"Remove program Minishell"$(RESET)

re: fclean all

.PHONY: all clean fclean re
