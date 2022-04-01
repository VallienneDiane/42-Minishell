# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 11:15:21 by amarchal          #+#    #+#              #
#    Updated: 2022/04/01 13:07:33 by dvallien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
LIB := ./libft/libft.a

DIR_SRCS := ./SRCS
LST_SRCS := main_diane.c		\
			chained_list.c		\
			path.c				\
			create_tabs.c 		\
			fill_tabs.c			\
			create_files.c		\
			redir_dup.c 		\
			exec_pipex.c		\
			exec_builtin.c		\
			echo.c				\
			heredoc.c 			\
			pwd.c 				\
			
DIR_OBJS := ./.OBJS
LST_OBJS := $(LST_SRCS:.c=.o)

SRCS := $(addprefix $(DIR_SRCS)/, $(LST_SRCS))
OBJS := $(addprefix $(DIR_OBJS)/, $(LST_OBJS))
INCLUDE := ./INCLUDES/minishell.h

CC := gcc
CFLAGS := -Wall -Wextra -Werror

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c $(INCLUDE)
		@mkdir -p $(DIR_OBJS)
		$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

all : libft $(NAME)
		@printf "\033[0;32mProject is ready to run !\033[0m\n"

libft :
		@make -C ./libft

$(NAME) : $(OBJS) $(LIB)
		$(CC) $(OBJS) $(LIB) -lreadline -o $(NAME)
		@printf "\033[0;32mCompilation has succeeded !\033[0m\n"

DIR_OBJS :
		mkdir -p $(DIR_OBJS)

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