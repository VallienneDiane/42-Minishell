# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 11:15:21 by amarchal          #+#    #+#              #
#    Updated: 2022/04/29 14:15:04 by dvallien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
LIB := ./libft/libft.a

DIR_SRCS := ./SRCS
LST_SRCS := main/main.c					\
			main/signal.c				\
			main/free.c					\
			parsing/chained_list_env.c	\
			parsing/chained_list.c		\
			parsing/cpy_env.c			\
			parsing/lexer.c				\
			parsing/parser_env_join.c	\
			parsing/parser_env_name.c	\
			parsing/parser_env_size.c	\
			parsing/parser_quote.c		\
			parsing/redir.c				\
			execution/create_files.c	\
			execution/create_tabs.c 	\
			execution/exec_builtins.c	\
			execution/exec_pipex.c		\
			execution/fill_tabs.c		\
			execution/heredoc.c 		\
			execution/path.c			\
			execution/redir_dup.c 		\
			execution/start_exec.c		\
			builtins/cd.c				\
			builtins/echo.c				\
			builtins/env.c				\
			builtins/exit.c				\
			builtins/export.c			\
			builtins/export_print.c		\
			builtins/pwd.c 				\
			builtins/unset.c				
			
DIR_OBJS := ./.OBJS
LST_OBJS := $(LST_SRCS:.c=.o)

SUB_DIR	:= 	main		\
			parsing		\
			execution	\
			builtins	\

SRCS := $(addprefix $(DIR_SRCS)/, $(LST_SRCS))
OBJS := $(addprefix $(DIR_OBJS)/, $(LST_OBJS))
INCLUDE := ./INCLUDES/minishell.h
READLINE_LIB := -L$(shell brew --prefix readline)/lib
READLINE_INC := -I$(shell brew --prefix readline)/include

CC := gcc
CFLAGS := -Wall -Wextra -Werror

READLINE_LIB := -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC := -I /Users/$(USER)/.brew/opt/readline/include

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c $(INCLUDE)
		@mkdir -p $(DIR_OBJS) $(addprefix $(DIR_OBJS)/, $(SUB_DIR))
		$(CC) $(CFLAGS) -I $(INCLUDE) $(READLINE_INC) -c $< -o $@

all : libft $(NAME)
		@printf "\033[0;32mProject is ready to run !\033[0m\n"

libft :
		@make -C ./libft

$(NAME) : $(OBJS) $(LIB)
		$(CC) $(OBJS) $(LIB) -lreadline $(READLINE_LIB) $(READLINE_INC) -o $(NAME)
		@printf "\033[0;32mCompilation has succeeded !\033[0m\n"

DIR_OBJS :
		mkdir -p $(DIR_OBJS) $(addprefix $(DIR_OBJS)/, $(SUB_DIR))

clean:
		@rm -rf $(DIR_OBJS)
		@make clean -C ./libft
		@printf "\033[0;33mMinishell's objects deleted\033[0m\n"

fclean:	clean
		@rm -rf $(NAME)
		@rm -rf $(LIB)
		@printf "\033[0;33m$(LIB) deleted\033[0m\n"
		@printf "\033[0;33m./$(NAME) deleted\033[0m\n"

re:		fclean all

norme :
		@printf "\033[36mNorminette :\033[0m\n"
		norminette $(SRCS) $(INCLUDE) ./libft

.PHONY:	all clean fclean re libft