# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 17:37:04 by yyean-wa          #+#    #+#              #
#    Updated: 2024/12/31 13:08:31 by yyean-wa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

AR = ar rcs
RM = rm -rf
ASAN = -fsanitize=address -g3
VAL = -ggdb3
CFLAGS = -Wall -Wextra -Werror -I./includes/ -I/usr/include/readline/

SRC_FILES = main lexer parser expansion \
			redirect execution child_process built-in built-in_2 \
			signal free utils utils2
SRC = $(addprefix src/, $(addsuffix .c,  $(SRC_FILES)))

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

#object files
OBJ_DIR = objs
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

test: CFLAGS += $(VAL)
test: fclean clean $(OBJ)
	@make test -C $(LIBFT_PATH) --no-print-directory
	@cc $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)
	@echo $(GREEN)"Minishell detail debug --ready."$(RESET)

debug: CFLAGS += $(ASAN)
debug: fclean clean $(OBJ)
	@make debug -C $(LIBFT_PATH) --no-print-directory
	@cc $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)
	@echo $(GREEN)"Minishell with ASAN  -ready."$(RESET)

$(LIBFT):
	@make -C $(LIBFT_PATH) --no-print-directory
	@make bonus -C $(LIBFT_PATH) --no-print-directory

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make clean -C $(LIBFT_PATH) --no-print-directory
	@$(RM) $(OBJ_DIR)
	@echo  $(YELLOW)"Remove objs file"$(RESET)

fclean: clean
	@make fclean -C $(LIBFT_PATH) --no-print-directory | grep -v "Remove libft's objs file"
	@$(RM) $(NAME)
	@echo $(YELLOW)"Remove program Minishell"$(RESET)

re: fclean all

.PHONY: all clean fclean re debug test

    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #         佛祖保佑           永无BUG
    #        God Bless        Never Crash
    #                   _oo0oo_
    #                  o8888888o
    #                  88" . "88
    #                  (| -_- |)
    #                  0\  =  /0
    #                ___/`---'\___
    #              .' \\|     |// '.
    #             | \\|||  :  |||// |
    #            / _||||| -:- |||||- \
    #           |   | \\\  -  /// |   |
    #           | \_|  ''\---/''  |_/ |
    #           \  .-\__  '-'  ___/-. /
    #         ___'. .'  /--.--\  `. .'___
    #      ."" '<  `.___\_<|>_/___.' >' "".
    #     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
    #     \  \ `_.   \_ __\ /__ _/   .-` /  /
    # =====`-.____`.___ \_____/___.-`___.-'=====
    #                   `=---='
    #     佛曰:
    #         写字楼里写字间，写字间里程序员；
    #         程序人员写程序，又拿程序换酒钱。
    #         酒醒只在网上坐，酒醉还来网下眠；
    #         酒醉酒醒日复日，网上网下年复年。
    #         但愿老死电脑间，不愿鞠躬老板前；
    #         奔驰宝马贵者趣，公交自行程序员。
    #         别人笑我忒疯癫，我笑自己命太贱；
    #         不见满街漂亮妹，哪个归得程序员？
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
