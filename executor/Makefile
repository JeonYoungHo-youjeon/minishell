# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/17 15:50:40 by mher              #+#    #+#              #
#    Updated: 2022/05/31 02:38:23 by mher             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
	
NAME	= test

RM	= rm -f
CC	= gcc -fsanitize=address -g3
CFLAGS	= -Wall -Wextra -Werror
READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

FT_DIR	= ./libft
FT 	= ft
GNL_DIR	= ./libgnl	
GNL	= gnl

SRCS	= \
	  ./builtins/ft_pwd.c \
	  ./builtins/ft_env.c \
	  ./builtins/ft_cd.c \
	  ./builtins/ft_echo.c \
	  ./builtins/ft_export.c \
	  ./builtins/ft_unset.c \
	  ./builtins/ft_exit.c \
	  ./builtins/env_utils.c \
	  executor.c \
	  fd_handling.c \
	  heredoc.c \
	  path.c \
	  test.c \

OBJS	= $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(MAKE) -C $(FT_DIR) 
	$(MAKE) -C $(GNL_DIR) 
	$(CC) $(CFLAGS) -o  $@ $^ \
		-L$(FT_DIR) -l$(FT) \
		-L$(GNL_DIR) -l$(GNL) \
		$(READLINE_LIB) \
		$(READLINE_INC) \

all : $(NAME)

clean :
	$(MAKE) clean -C $(FT_DIR)
	$(MAKE) clean -C $(GNL_DIR)
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) fclean -C $(FT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)
	$(RM) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re
