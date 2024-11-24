# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 17:37:04 by yyean-wa          #+#    #+#              #
#    Updated: 2024/11/25 00:20:41 by zgoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

AR = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -Iincludes/

SRC_FILES = main lexer parser signal utils
SRC = $(addprefix src/, $(addsuffix .c,  $(SRC_FILES)))

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

#object files
OBJ_DIR = objs/
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@cc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@cc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "Minishell ready."

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make bonus -C $(LIBFT_PATH)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJ_DIR)
	@echo "Remove objs file"

fclean: clean
	@make fclean -C $(LIBFT_PATH) | grep -v "Remove libft's objs file"
	@$(RM) $(NAME)
	@echo "Remove program Minishell"

re: fclean all

.PHONY: all clean fclean re
